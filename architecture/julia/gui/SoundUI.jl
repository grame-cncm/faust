# ************************************************************************
# FAUST Architecture File
# Copyright (C) 2026 GRAME, Centre National de Creation Musicale
# ---------------------------------------------------------------------

# This is sample code. This file is provided as an example of minimal
# FAUST architecture file. Redistribution and use in source and binary
# forms, with or without modification, in part or in full are permitted.
# In particular you can create a derived work of this FAUST architecture
# and distribute that work under terms of your choice.

# This sample code is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# ************************************************************************

# Architectures files
include("/usr/local/share/faust/julia/dsp/dsp.jl")
include("/usr/local/share/faust/julia/gui/UI.jl")

#=
Loading of the sound files used by the 'soundfile' primitive (see faust/gui/SoundUI.h).

A reader is a subtype of SoundfileReader which implements:
- checkFile(reader, path_name) -> Bool
- getParamsFile(reader, path_name) -> (channels, length)
- readFile!(reader, soundfile, path_name, part, offset) -> new offset

where 'part' and 'offset' start at 0, like in the C++ version.
=#
abstract type SoundfileReader end

checkFile(reader::SoundfileReader, path_name::String) = isfile(path_name)

# Return the list of file names of a soundfile URL: "{'foo.wav';'bar.wav'}" or "foo.wav"
function parseSoundfileURL(url::String)
    url = strip(url)
    if startswith(url, "{") && endswith(url, "}")
        return [String(strip(strip(item), '\'')) for item in split(url[2:end-1], ';')]
    else
        return [String(url)]
    end
end

# Return the real path of 'file_name', or "" if it cannot be found
function checkSoundfile(reader::SoundfileReader, directories::Vector{String}, file_name::String)
    checkFile(reader, file_name) && return file_name
    for dir in directories
        path_name = joinpath(dir, file_name)
        checkFile(reader, path_name) && return path_name
    end
    return ""
end

function emptyFile!(soundfile::Soundfile, part::Int, offset::Int)
    soundfile.fLength[part+1] = SOUNDFILE_BUFFER_SIZE
    soundfile.fSR[part+1] = SOUNDFILE_SAMPLE_RATE
    soundfile.fOffset[part+1] = offset
    return offset + SOUNDFILE_BUFFER_SIZE
end

# Create a Soundfile{T} with all the files of 'path_name_list' ("" for a missing file)
function createSoundfile(reader::SoundfileReader, ::Type{T}, path_name_list::Vector{String}) where {T}
    nparts = length(path_name_list)
    nparts > MAX_SOUNDFILE_PARTS && error("too many sound files: $nparts > $MAX_SOUNDFILE_PARTS")
    channels = 1  # at least one channel
    total_length = (MAX_SOUNDFILE_PARTS - nparts) * SOUNDFILE_BUFFER_SIZE
    for path_name in path_name_list
        chan, len = (path_name == "") ? (1, SOUNDFILE_BUFFER_SIZE) : getParamsFile(reader, path_name)
        channels = max(channels, chan)
        total_length += len
    end
    soundfile = Soundfile{T}([zeros(T, total_length) for _ in 1:channels],
                             zeros(Int32, MAX_SOUNDFILE_PARTS),
                             zeros(Int32, MAX_SOUNDFILE_PARTS),
                             zeros(Int32, MAX_SOUNDFILE_PARTS),
                             Int32(channels), Int32(nparts), T == Float64)
    offset = 0
    for (part, path_name) in enumerate(path_name_list)
        offset = (path_name == "") ? emptyFile!(soundfile, part - 1, offset) :
                 readFile!(reader, soundfile, path_name, part - 1, offset)
    end
    for part in nparts:MAX_SOUNDFILE_PARTS-1
        offset = emptyFile!(soundfile, part, offset)
    end
    return soundfile
end

# The type of the soundfile field of a DSP (Soundfile{T})
soundfileType(dsp::dsp, field::Symbol) = fieldtype(typeof(dsp), field).parameters[1]

# Create the soundfile of an 'url', looking for the files in 'directories'
function loadSoundfile(reader::SoundfileReader, ::Type{T}, url::String, directories::Vector{String}) where {T}
    path_name_list = String[]
    for file_name in parseSoundfileURL(url)
        path_name = checkSoundfile(reader, directories, file_name)
        # A missing file is replaced by an empty sound (= silence)
        path_name == "" && println(stderr, "addSoundfile : soundfile $file_name cannot be found !")
        push!(path_name_list, path_name)
    end
    return createSoundfile(reader, T, path_name_list)
end

# -- MemoryReader: 2 silent channels of 4096 frames for any name (to be subtyped)
struct MemoryReader <: SoundfileReader end

checkFile(::MemoryReader, path_name::String) = true
getParamsFile(::MemoryReader, path_name::String) = (2, 4096)
function readFile!(::MemoryReader, soundfile::Soundfile, path_name::String, part::Int, offset::Int)
    soundfile.fLength[part+1] = 4096
    soundfile.fSR[part+1] = 44100
    soundfile.fOffset[part+1] = offset
    return offset + 4096
end

# -- WAVReader: PCM 8/16/24/32 bits and IEEE float 32/64 bits WAV files, without resampling
struct WAVReader <: SoundfileReader end

struct WAVInfo
    format::UInt16
    channels::Int
    sample_rate::Int
    bits::Int
    data_offset::Int
    frames::Int
end

function wavInfo(path_name::String)
    open(path_name) do io
        String(read(io, 4)) == "RIFF" || error("$path_name is not a RIFF file")
        read(io, UInt32)
        String(read(io, 4)) == "WAVE" || error("$path_name is not a WAVE file")
        format = 0x0000; channels = 0; sample_rate = 0; bits = 0
        while !eof(io)
            id = String(read(io, 4))
            size = Int(ltoh(read(io, UInt32)))
            if id == "fmt "
                start = position(io)
                format = ltoh(read(io, UInt16))
                channels = Int(ltoh(read(io, UInt16)))
                sample_rate = Int(ltoh(read(io, UInt32)))
                read(io, UInt32); read(io, UInt16)
                bits = Int(ltoh(read(io, UInt16)))
                if format == 0xFFFE  # WAVE_FORMAT_EXTENSIBLE: the format is in the sub-format GUID
                    read(io, UInt16); read(io, UInt16); read(io, UInt32)
                    format = ltoh(read(io, UInt16))
                end
                seek(io, start + size + isodd(size))
            elseif id == "data"
                channels > 0 || error("$path_name: 'data' chunk before 'fmt ' chunk")
                return WAVInfo(format, channels, sample_rate, bits, position(io),
                               size ÷ (channels * (bits ÷ 8)))
            else
                skip(io, size + isodd(size))
            end
        end
        error("$path_name has no 'data' chunk")
    end
end

checkFile(::WAVReader, path_name::String) =
    isfile(path_name) && try wavInfo(path_name); true catch; false end

function getParamsFile(::WAVReader, path_name::String)
    info = wavInfo(path_name)
    return (info.channels, info.frames)
end

function readWAVSample(io::IO, info::WAVInfo)
    if info.format == 3  # IEEE float
        return info.bits == 32 ? Float64(ltoh(read(io, Float32))) : ltoh(read(io, Float64))
    elseif info.bits == 8   # unsigned
        return (Int(read(io, UInt8)) - 128) / 128.0
    elseif info.bits == 16
        return ltoh(read(io, Int16)) / 32768.0
    elseif info.bits == 24
        b = read(io, 3)
        v = Int32(b[1]) | (Int32(b[2]) << 8) | (Int32(b[3]) << 16)
        return ((v << 8) >> 8) / 8388608.0  # sign extension
    elseif info.bits == 32
        return ltoh(read(io, Int32)) / 2147483648.0
    else
        error("unsupported WAV sample size: $(info.bits) bits")
    end
end

function readFile!(::WAVReader, soundfile::Soundfile{T}, path_name::String, part::Int, offset::Int) where {T}
    info = wavInfo(path_name)
    (info.format == 1 || info.format == 3) || error("$path_name: unsupported WAV format $(info.format)")
    soundfile.fLength[part+1] = info.frames
    soundfile.fSR[part+1] = info.sample_rate
    soundfile.fOffset[part+1] = offset
    open(path_name) do io
        seek(io, info.data_offset)
        for frame in 1:info.frames, chan in 1:info.channels
            soundfile.fBuffers[chan][offset + frame] = T(readWAVSample(io, info))
        end
    end
    return offset + info.frames
end

# -- SoundUI: load the soundfiles of a DSP when 'buildUserInterface!' is called
mutable struct SoundUI <: UI
    SoundUI(dsp::dsp, reader::SoundfileReader = WAVReader(), directories::Vector{String} = String[]) =
        new(dsp, reader, directories)
    dsp::dsp
    reader::SoundfileReader
    directories::Vector{String}
end

function addSoundfile!(ui_interface::SoundUI, label::String, url::String, soundfile::Symbol)
    dsp = ui_interface.dsp
    sf = loadSoundfile(ui_interface.reader, soundfileType(dsp, soundfile), url, ui_interface.directories)
    setproperty!(dsp, soundfile, sf)
end
