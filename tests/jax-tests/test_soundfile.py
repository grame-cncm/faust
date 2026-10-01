"""Soundfile loading and Linen channel/gradient regressions."""

from pathlib import Path
from types import SimpleNamespace
import subprocess

import jax
import jax.numpy as jnp
import numpy as np
import pytest
from scipy.io import wavfile

from test_utils import load_module


@pytest.fixture(params=["nnx", "linen"])
def soundfile_module(request, faust_compiler, jax_architecture_dir,
                     jax_library_dir, tmp_path):
    language = request.param
    arch = "minimal.py" if language == "nnx" else "minimal_linen.py"
    output = tmp_path / f"soundfile_{language}.py"
    subprocess.run([
        str(faust_compiler), "-lang", language,
        "-a", str(jax_architecture_dir / arch), "-I", str(jax_library_dir),
        str(Path(__file__).parent / "dsp" / "simple_gain.dsp"), "-o", str(output),
    ], check=True, capture_output=True, text=True)
    return load_module(output, module_name=f"soundfile_{language}")


def test_directory_fallback(soundfile_module, tmp_path, monkeypatch):
    """Missing cwd and directory candidates must not trigger decoder warnings."""
    directory = tmp_path / "audio"
    directory.mkdir()
    audio = np.stack([np.arange(8), np.arange(8) + 10], axis=1).astype(np.float32)
    wavfile.write(directory / "test.wav", 44100, audio)
    monkeypatch.chdir(tmp_path)
    loader = SimpleNamespace(soundfile_dirs=[str(tmp_path / "missing"), str(directory)])
    loaded, sr = soundfile_module.mydsp.load_soundfile(loader, "test.wav")
    np.testing.assert_array_equal(loaded, audio.T)
    assert sr == 44100


def test_missing_paths_reported(soundfile_module, tmp_path, monkeypatch):
    monkeypatch.chdir(tmp_path)
    missing = tmp_path / "missing"
    loader = SimpleNamespace(soundfile_dirs=[str(missing)])
    with pytest.raises(soundfile_module.SoundfileLoadError) as error:
        soundfile_module.mydsp.load_soundfile(loader, "absent.wav")
    assert "Attempted paths: absent.wav" in str(error.value)
    assert str(missing / "absent.wav") in str(error.value)


def test_existing_decode_error_stops_search(soundfile_module, tmp_path, monkeypatch):
    candidate = tmp_path / "broken.wav"
    candidate.write_bytes(b"invalid audio")
    calls = []

    def fail(path, **kwargs):
        calls.append(path)
        raise RuntimeError("decode failed")

    monkeypatch.setattr(soundfile_module.librosa, "load", fail)
    loader = SimpleNamespace(soundfile_dirs=[str(tmp_path / "other")])
    with pytest.raises(soundfile_module.SoundfileLoadError, match="decode failed") as error:
        soundfile_module.mydsp.load_soundfile(loader, str(candidate))
    assert isinstance(error.value.__cause__, RuntimeError)
    assert calls == [str(candidate)]


@pytest.mark.integration
@pytest.mark.parametrize("learnable", [False, True])
@pytest.mark.parametrize("jit", [False, True])
def test_linen_channel_wrap(faust_compiler, jax_architecture_dir, jax_library_dir,
                           tmp_path, learnable, jit):
    name = "soundfile_channel_wrap_learnable.dsp" if learnable else "soundfile_channel_wrap.dsp"
    output = tmp_path / "wrap.py"
    subprocess.run([
        str(faust_compiler), "-lang", "linen", "-a", str(jax_architecture_dir / "minimal_linen.py"),
        "-I", str(jax_library_dir), str(Path(__file__).parent / "dsp" / name), "-o", str(output),
    ], check=True, capture_output=True, text=True)
    module = load_module(output, module_name="linen_soundfile_wrap")
    audio = np.stack([np.arange(1, 9), np.arange(10, 90, 10)], axis=1).astype(np.float32)
    wavfile.write(tmp_path / "channel_wrap.wav", 44100, audio)
    model = module.mydsp(sample_rate=44100, faust_float=jnp.float32,
                         soundfile_dirs=(str(tmp_path),))
    inputs = jnp.zeros((0, 8), dtype=jnp.float32)
    variables = model.init(jax.random.key(0), inputs)
    apply = jax.jit(model.apply) if jit else model.apply
    result = apply(variables, inputs)
    assert result.shape == (4, 8)
    assert not np.array_equal(result[0], result[1])
    np.testing.assert_array_equal(result[2], result[0])
    np.testing.assert_array_equal(result[3], result[1])
    if learnable:
        key = next(k for k in variables["params"] if "fBuffers" in k)
        assert variables["params"][key].shape == (2, 8)
        grads = jax.grad(lambda p: jnp.sum(model.apply({"params": p}, inputs)))(variables["params"])
        # Both aliases contribute to the same physical channel's parameter.
        np.testing.assert_array_equal(grads[key].sum(axis=1), [16, 16])
