#!/usr/bin/env python3
"""JDK preflight and strict checks for Java double impulse responses."""
import argparse
import json
import math
import os
from pathlib import Path
import platform
import re
import shlex
import shutil
import subprocess
import sys
import tempfile


FRAMES = 15000
SAMPLE = re.compile(r"[-+]?(?:[0-9]+(?:\.[0-9]*)?|\.[0-9]+)(?:[eE][-+]?[0-9]+)?")


def tool(explicit, name):
    if explicit:
        return explicit
    home = os.environ.get('JAVA_HOME')
    if not home and platform.system() == 'Darwin':
        probe = subprocess.run(['/usr/libexec/java_home'], capture_output=True, text=True)
        if probe.returncode == 0:
            home = probe.stdout.strip()
    return str(Path(home) / 'bin' / name) if home else (shutil.which(name) or name)


def execute(command, **kwargs):
    print('+ ' + shlex.join(map(str, command)), flush=True)
    subprocess.run(command, check=True, **kwargs)


def validate(path, frames=FRAMES, prefix=False):
    """Reject malformed, truncated and non-finite data before filesCompare."""
    with Path(path).open() as stream:
        header = []
        for key in ('number_of_inputs', 'number_of_outputs', 'number_of_frames'):
            fields = stream.readline().split()
            if (len(fields) != 3 or fields[:2] != [key, ':']
                    or not re.fullmatch(r'[0-9]+', fields[2])):
                raise ValueError(f'{path}: invalid {key} header')
            header.append(int(fields[2]))
        inputs, outputs, declared = header
        if inputs < 0 or outputs < 0 or (declared < frames if prefix else declared != frames):
            raise ValueError(f'{path}: invalid dimensions or frame count {header}')
        for index in range(frames):
            fields = stream.readline().split()
            if len(fields) != outputs + 2 or fields[1] != ':' or fields[0] != str(index):
                raise ValueError(f'{path}: invalid row/index/channel count at frame {index}')
            if any(not SAMPLE.fullmatch(value) or not math.isfinite(float(value)) for value in fields[2:]):
                raise ValueError(f'{path}: invalid or non-finite value at frame {index}')
        if not prefix and stream.read():
            raise ValueError(f'{path}: extra data after frame {frames - 1}')
    return inputs, outputs


def negative_controls(compare):
    with tempfile.TemporaryDirectory(prefix='faust-java-check-') as directory:
        root = Path(directory)
        reference, candidate = root / 'reference.ir', root / 'candidate.ir'
        valid = 'number_of_inputs : 1\nnumber_of_outputs : 1\nnumber_of_frames : 3\n0 : 1.0\n1 : 0.0\n2 : 0.0\n'
        reference.write_text(valid)
        validate(reference, frames=3)
        execute([compare, str(reference), str(reference)])
        corruptions = {
            'truncated': valid.rsplit('2 :', 1)[0],
            'empty': '',
            'index': valid.replace('1 : 0.0', '7 : 0.0'),
            'channel': valid.replace('1 : 0.0', '1 : 0.0 0.0'),
            'nan': valid.replace('1 : 0.0', '1 : NaN'),
            'infinity': valid.replace('1 : 0.0', '1 : Infinity'),
            'header': valid.replace('number_of_inputs', 'wrong_header'),
            'frames': valid.replace('number_of_frames : 3', 'number_of_frames : 2'),
            'extra': valid + '3 : 0.0\n',
            'numeric suffix': valid.replace('1 : 0.0', '1 : 0.0junk'),
            'numeric separator': valid.replace('1 : 0.0', '1 : 0_0'),
        }
        for name, content in corruptions.items():
            candidate.write_text(content)
            try:
                validate(candidate, frames=3)
            except (ValueError, IndexError):
                print(f'PASS negative control: {name}', flush=True)
            else:
                raise AssertionError(f'Validator accepted {name} output')
        candidate.write_text(valid.replace('0 : 1.0', '0 : 2.0'))
        validate(candidate, frames=3)
        for options in ([], ['-part']):
            verdict = subprocess.run([compare, str(candidate), str(reference), *options], capture_output=True, text=True)
            print('Expected rejection of altered value ' + ('(prefix):' if options else '(full):'), file=sys.stderr)
            print(verdict.stdout, end='')
            print(verdict.stderr, end='', file=sys.stderr)
            if verdict.returncode != 1 or 'delta' not in verdict.stderr:
                raise AssertionError('Comparator failed its altered-value negative control')
        print('PASS negative control: altered value', flush=True)


def prepare(args):
    execute([args.faust, '--version'])
    java, javac = tool(args.java, 'java'), tool(args.javac, 'javac')
    javaflags, javacflags = shlex.split(args.javaflags), shlex.split(args.javacflags)
    try:
        execute([javac, '-version'])
        execute([java, '-version'])
        with tempfile.TemporaryDirectory(prefix='faust-jdk-') as directory:
            source = Path(directory) / 'FaustJdkProbe.java'
            source.write_text('class FaustJdkProbe { public static void main(String[] args) { System.out.println("JDK compile/run: OK"); } }\n')
            execute([javac, *javacflags, '-d', directory, str(source)])
            execute([java, *javaflags, '-cp', directory, 'FaustJdkProbe'])
    except (OSError, subprocess.CalledProcessError) as error:
        raise RuntimeError('A working JDK is required. Set JAVA_HOME to its installation directory, '
                           'or pass JAVA=/path/to/bin/java JAVAC=/path/to/bin/javac. '
                           f'Attempted java={java}, javac={javac}: {error}') from error
    negative_controls(args.compare)
    config = Path(args.config)
    config.parent.mkdir(parents=True, exist_ok=True)
    config.write_text(json.dumps(dict(java=java, javac=javac, javaflags=javaflags, javacflags=javacflags)))


def compile_source(args, config):
    execute([config['javac'], *config['javacflags'], '-d', str(Path(args.source).parent), args.source])


def run_case(args, config):
    reference_shape = validate(args.reference, prefix=True)
    responses = []
    modes = ('fixed',) if args.fixed_only else ('fixed', 'fragmented')
    for mode in modes:
        output = Path(f'{args.output}.{mode}.ir')
        temporary = output.with_suffix('.tmp')
        output.unlink(missing_ok=True)
        try:
            with temporary.open('w') as stream:
                execute([config['java'], *config['javaflags'], '-cp', args.classes, 'Impulse', mode], stdout=stream)
            if validate(temporary) != reference_shape:
                raise ValueError(f'{temporary}: input/output dimensions differ from reference')
            execute([args.compare, str(temporary), args.reference, '-part'])
            temporary.replace(output)
        finally:
            temporary.unlink(missing_ok=True)
        responses.append(output)
    if len(responses) == 2:
        execute([args.compare, *map(str, responses)])
    else:
        print('SKIP fragmented bs.dsp: its foreign count variable observes compute block size', flush=True)
    print(f'PASS {Path(args.output).name}: {len(responses)} reference comparisons, {len(responses) - 1} block-partition comparisons, {FRAMES} frames each', flush=True)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('action', choices=('prepare', 'compile', 'run'))
    parser.add_argument('--config', required=True)
    parser.add_argument('--faust')
    parser.add_argument('--java', default='')
    parser.add_argument('--javac', default='')
    parser.add_argument('--javaflags', default='')
    parser.add_argument('--javacflags', default='')
    parser.add_argument('--compare', default='./filesCompare')
    parser.add_argument('--source')
    parser.add_argument('--classes')
    parser.add_argument('--output')
    parser.add_argument('--reference')
    parser.add_argument('--fixed-only', action='store_true')
    args = parser.parse_args()
    if args.action == 'prepare':
        prepare(args)
    else:
        config = json.loads(Path(args.config).read_text())
        if args.action == 'compile':
            compile_source(args, config)
        else:
            run_case(args, config)


if __name__ == '__main__':
    try:
        main()
    except (OSError, ValueError, RuntimeError, subprocess.CalledProcessError, AssertionError) as error:
        print(f'Java impulse test failed: {error}', file=sys.stderr)
        sys.exit(1)
