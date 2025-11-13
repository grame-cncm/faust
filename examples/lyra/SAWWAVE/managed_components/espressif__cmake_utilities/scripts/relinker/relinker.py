#!/usr/bin/env python3
#
# SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
# SPDX-License-Identifier: Apache-2.0


import logging
import argparse
import csv
import os
import subprocess
import sys
import re
from io import StringIO
import configuration

sys.path.append(os.environ['IDF_PATH'] + '/tools/ldgen')
sys.path.append(os.environ['IDF_PATH'] + '/tools/ldgen/ldgen')
from entity import EntityDB

espidf_objdump = None

def lib_secs(lib, file, lib_path):
    new_env = os.environ.copy()
    new_env['LC_ALL'] = 'C'
    dump = StringIO(subprocess.check_output([espidf_objdump, '-h', lib_path], env=new_env).decode())
    dump.name = lib

    sections_infos = EntityDB()
    sections_infos.add_sections_info(dump)

    secs = sections_infos.get_sections(lib, file.split('.')[0] + '.c')
    if len(secs) == 0:
        secs = sections_infos.get_sections(lib, file.split('.')[0])
        if len(secs) == 0:
            raise ValueError('Failed to get sections from lib %s'%(lib_path))
    
    return secs

def filter_secs(secs_a, secs_b):
    new_secs = list()
    for s_a in secs_a:
        for s_b in secs_b:
            if s_b in s_a:
                new_secs.append(s_a)
    return new_secs

def strip_secs(secs_a, secs_b):
    secs = list(set(secs_a) - set(secs_b))
    secs.sort()
    return secs

def func2sect(func):
    if ' ' in func:
        func_l = func.split(' ')
    else:
        func_l = list()
        func_l.append(func)
    
    secs = list()
    for l in func_l:
        if '.iram1.' not in l:
            secs.append('.literal.%s'%(l,))
            secs.append('.text.%s'%(l, ))
        else:
            secs.append(l)
    return secs

class filter_c:
    def __init__(self, file):
        lines = open(file).read().splitlines()
        self.libs_desc = ''
        self.libs = ''
        for l in lines:
            if ') .iram1 EXCLUDE_FILE(*' in l and ') .iram1.*)' in l:
                desc = '\(EXCLUDE_FILE\((.*)\) .iram1 '
                self.libs_desc = re.search(desc, l)[1]
                self.libs = self.libs_desc.replace('*', '')
                return
    
    def match(self, lib):
        if lib in self.libs:
            print('Remove lib %s'%(lib))
            return True
        return False
    
    def add(self):
        return self.libs_desc

class target_c:
    def __init__(self, lib, lib_path, file, fsecs):
        self.lib   = lib
        self.file  = file

        self.lib_path  = lib_path
        self.fsecs = func2sect(fsecs)
        self.desc  = '*%s:%s.*'%(lib, file.split('.')[0])

        secs = lib_secs(lib, file, lib_path)
        if '.iram1.' in self.fsecs[0]:
            self.secs = filter_secs(secs, ('.iram1.', ))
        else:
            self.secs = filter_secs(secs, ('.iram1.', '.text.', '.literal.'))
        self.isecs = strip_secs(self.secs, self.fsecs)

    def __str__(self):
        s = 'lib=%s\nfile=%s\lib_path=%s\ndesc=%s\nsecs=%s\nfsecs=%s\nisecs=%s\n'%(\
            self.lib, self.file, self.lib_path, self.desc, self.secs, self.fsecs,\
            self.isecs)
        return s

class relink_c:
    def __init__(self, input, library_file, object_file, function_file, sdkconfig_file, missing_function_info):
        self.filter = filter_c(input)
        
        libraries = configuration.generator(library_file, object_file, function_file, sdkconfig_file, missing_function_info, espidf_objdump)
        self.targets = list()
        for i in libraries.libs:
            lib = libraries.libs[i]

            if self.filter.match(lib.name):
                continue

            for j in lib.objs:
                obj = lib.objs[j]
                self.targets.append(target_c(lib.name, lib.path, obj.name,
                                             ' '.join(obj.sections())))
        # for i in self.targets:
        #     print(i)
        self.__transform__()

    def __transform__(self):
        iram1_exclude = list()
        iram1_include = list()
        flash_include = list()

        for t in self.targets:
            secs = filter_secs(t.fsecs, ('.iram1.', ))
            if len(secs) > 0:
                iram1_exclude.append(t.desc)

            secs = filter_secs(t.isecs, ('.iram1.', ))
            if len(secs) > 0:
                iram1_include.append('    %s(%s)'%(t.desc, ' '.join(secs)))

            secs = t.fsecs
            if len(secs) > 0:
                flash_include.append('    %s(%s)'%(t.desc, ' '.join(secs)))

        self.iram1_exclude = '    *(EXCLUDE_FILE(%s %s) .iram1.*) *(EXCLUDE_FILE(%s %s) .iram1)' % \
                             (self.filter.add(), ' '.join(iram1_exclude), \
                              self.filter.add(), ' '.join(iram1_exclude))
        self.iram1_include = '\n'.join(iram1_include)
        self.flash_include = '\n'.join(flash_include)

        logging.debug('IRAM1 Exclude: %s'%(self.iram1_exclude))
        logging.debug('IRAM1 Include: %s'%(self.iram1_include))
        logging.debug('Flash Include: %s'%(self.flash_include))

    def __replace__(self, lines):
        def is_iram_desc(l):
            if '*(.iram1 .iram1.*)' in l or (') .iram1 EXCLUDE_FILE(*' in l and ') .iram1.*)' in l):
                return True
            return False

        iram_start = False
        flash_done = False

        for i in range(0, len(lines) - 1):
            l = lines[i]
            if '.iram0.text :' in l:
                logging.debug('start to process .iram0.text')
                iram_start = True
            elif '.dram0.data :' in l:
                logging.debug('end to process .iram0.text')
                iram_start = False
            elif is_iram_desc(l):
                if iram_start:
                    lines[i] = '%s\n%s\n'%(self.iram1_exclude, self.iram1_include)
            elif '(.stub .gnu.warning' in l:
                if not flash_done:
                    lines[i] = '%s\n\n%s'%(self.flash_include, l)
            elif self.flash_include in l:
                flash_done = True
            else:
                if iram_start:
                    new_l = self._replace_func(l)
                    if new_l:
                        lines[i] = new_l

        return lines

    def _replace_func(self, l):
        for t in self.targets:
            if t.desc in l:
                S = '.literal .literal.* .text .text.*'
                if S in l:
                    if len(t.isecs) > 0:
                        return l.replace(S, ' '.join(t.isecs))
                    else:
                        return ' '
                
                S = '%s(%s)'%(t.desc, ' '.join(t.fsecs))
                if S in l:
                    return ' '

                replaced = False
                for s in t.fsecs:
                    s2 = s + ' '
                    if s2 in l:
                        l = l.replace(s2, '')
                        replaced = True
                    s2 = s + ')'
                    if s2 in l:
                        l = l.replace(s2, ')')
                        replaced = True
                if '( )' in l or '()' in l:
                    return ' ' 
                if replaced:
                    return l
            else:
                index = '*%s:(EXCLUDE_FILE'%(t.lib)
                if index in l and t.file.split('.')[0] not in l:
                    for m in self.targets:
                        index = '*%s:(EXCLUDE_FILE'%(m.lib)
                        if index in l and m.file.split('.')[0] not in l:
                            l = l.replace('EXCLUDE_FILE(', 'EXCLUDE_FILE(%s '%(m.desc))
                            if len(m.isecs) > 0:
                                l += '\n    %s(%s)'%(m.desc, ' '.join(m.isecs))
                    return l

        return False

    def save(self, input, output):
        lines = open(input).read().splitlines()
        lines = self.__replace__(lines)
        open(output, 'w+').write('\n'.join(lines))

def main():
    argparser = argparse.ArgumentParser(description='Relinker script generator')

    argparser.add_argument(
        '--input', '-i',
        help='Linker template file',
        type=str)

    argparser.add_argument(
        '--output', '-o',
        help='Output linker script',
        type=str)

    argparser.add_argument(
        '--library', '-l',
        help='Library description directory',
        type=str)

    argparser.add_argument(
        '--object', '-b',
        help='Object description file',
        type=str)

    argparser.add_argument(
        '--function', '-f',
        help='Function description file',
        type=str)

    argparser.add_argument(
        '--sdkconfig', '-s',
        help='sdkconfig file',
        type=str)

    argparser.add_argument(
        '--objdump', '-g',
        help='GCC objdump command',
        type=str)
    
    argparser.add_argument(
        '--debug', '-d',
        help='Debug level(option is \'debug\')',
        default='no',
        type=str)
    
    argparser.add_argument(
        '--missing_function_info',
        help='Print error information instead of throwing exception when missing function',
        default=False,
        type=bool)

    args = argparser.parse_args()

    if args.debug == 'debug':
        logging.basicConfig(level=logging.DEBUG)

    logging.debug('input:    %s'%(args.input))
    logging.debug('output:   %s'%(args.output))
    logging.debug('library:  %s'%(args.library))
    logging.debug('object:   %s'%(args.object))
    logging.debug('function: %s'%(args.function))
    logging.debug('sdkconfig:%s'%(args.sdkconfig))
    logging.debug('objdump:  %s'%(args.objdump))
    logging.debug('debug:    %s'%(args.debug))
    logging.debug('missing_function_info: %s'%(args.missing_function_info))

    global espidf_objdump
    espidf_objdump = args.objdump

    relink = relink_c(args.input, args.library, args.object, args.function, args.sdkconfig, args.missing_function_info)
    relink.save(args.input, args.output)

if __name__ == '__main__':
    main()
