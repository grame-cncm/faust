#!/usr/bin/env python
#
# SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
#
# SPDX-License-Identifier: Apache-2.0

import sys
import struct
import argparse
import binascii
import hashlib
import os
import subprocess
import shutil
import json
import lzma

# src_file = 'hello-world.bin'
# compressed_file = 'hello-world.bin.xz'
# packed_compressed_file = 'hello-world.bin.xz.packed'
# siged_packed_compressed_file = 'hello-world.bin.xz.packed.signed'

binary_compress_type = {'none': 0, 'xz':1}
header_version = {'v1': 1, 'v2': 2, 'v3': 3}

SCRIPT_VERSION = '1.0.0'
ORIGIN_APP_IMAGE_HEADER_LEN = 288   # sizeof(esp_image_header_t) + sizeof(esp_image_segment_header_t) + sizeof(esp_app_desc_t). See esp_app_format.h
# At present, we calculate the checksum of the first 4KB data of the old app.                
OLD_APP_CHECK_DATA_SIZE = 4096      

# v1 compressed data header:
# Note: Encryption_type field is deprecated, the field is reserved for compatibility.
# |------|---------|---------|----------|------------|------------|-----------|----------|----------------|----------------|--------------|------------|
# |      | Magic   | header  | Compress | delta      | Encryption | Reserved  | Firmware | The length of  | The MD5 of     | The CRC32 for| compressed |
# |      | number  | version | type     | type       | type       |           | version  | compressed data| compressed data| the header   | data       |
# |------|---------|---------|----------|------------|------------|-----------|----------|----------------|----------------|--------------|------------|
# | Size | 4 bytes | 1 byte  | 4 bits	| 4 bits     | 1 bytes	  | 1 bytes   | 32 bytes |  4 bytes	      | 32 bytes	   |  4 bytes     |            |
# |------|---------|---------|----------|------------|------------|-----------|----------|----------------|----------------|--------------|------------|
# | Data | String  |         |          |            |            |           | String   | little-endian  |   byte string  | little-endian|            |
# | type | ended   |         |          |            |            |           | ended    |   integer      |                |    integer   |            |
# |      |with ‘\0’|         |          |            |            |           | with ‘\0’|                |                |              | Binary data|
# |------|---------|---------|----------|------------|------------|-----------|----------|----------------|----------------|--------------|------------|
# | Data | “ESP”   |    1    |   0/1    | 0/1        |	          |           |          |                |                |              |            |
# |------|---------|---------|----------|------------|------------|-----------|----------|----------------|----------------|--------------|------------|

# v2 compressed data header
# Note: Encryption_type field is deprecated, the field is reserved for compatibility.
# |------|---------|---------|----------|------------|------------|-----------|----------|----------------|----------------|---------------|---------------|--------------|------------|
# |      | Magic   | header  | Compress | delta      | Encryption | Reserved  | Firmware | The length of  | The MD5 of     | base app check| The CRC32 for | The CRC32 for| compressed |
# |      | number  | version | type     | type       | type       |           | version  | compressed data| compressed data| data len      | base app data | the header   | data       |
# |------|---------|---------|----------|------------|------------|-----------|----------|----------------|----------------|---------------|---------------|--------------|------------|
# | Size | 4 bytes | 1 byte  | 4 bits	| 4 bits     | 1 bytes	  | 1 bytes   | 32 bytes |  4 bytes	      | 32 bytes	   |  4 bytes      |  4 bytes      |  4 bytes     |            |
# |------|---------|---------|----------|------------|------------|-----------|----------|----------------|----------------|---------------|---------------|--------------|------------|
# | Data | String  |         |          |            |            |           | String   | little-endian  |   byte string  | little-endian | little-endian | little-endian|            |
# | type | ended   |         |          |            |            |           | ended    |   integer      |                | integer       |    integer    |    integer   |            |
# |      |with ‘\0’|         |          |            |            |           | with ‘\0’|                |                |               |               |              | Binary data|
# |------|---------|---------|----------|------------|------------|-----------|----------|----------------|----------------|---------------|---------------|--------------|------------|
# | Data | “ESP”   |    1    |   0/1    | 0/1        |	          |           |          |                |                |               |               |              |            |
# |------|---------|---------|----------|------------|------------|-----------|----------|----------------|----------------|---------------|---------------|--------------|------------|

# v3 compressed data header:
# |------|---------|---------|----------|------------|-----------|----------------|----------------|--------------|------------|
# |      | Magic   | header  | Compress | Reserved   | Reserved  | The length of  | The MD5 of     | The CRC32 for| compressed |
# |      | number  | version | type     |            |           | compressed data| compressed data| the header   | data       |
# |------|---------|---------|----------|------------|-----------|----------------|----------------|--------------|------------|
# | Size | 4 bytes | 1 byte  | 4 bits	| 4 bits     | 8 bytes   |  4 bytes	      |   16 bytes	   |  4 bytes     |            |
# |------|---------|---------|----------|------------|-----------|----------------|----------------|--------------|------------|
# | Data | String  | integer |          |            |           | little-endian  |   byte string  | little-endian|            |
# | type | ended   |         |          |            |           |   integer      |                |    integer   |            |
# |      |with ‘\0’|         |          |            |           |                |                |              | Binary data|
# |------|---------|---------|----------|------------|-----------|----------------|----------------|--------------|------------|
# | Data | “ESP”   |     3   |   0/1    |            |           |                |                |              |            |
# |------|---------|---------|----------|------------|-----------|----------------|----------------|--------------|------------|

def xz_compress(store_directory, in_file):
    compressed_file = ''.join([in_file,'.xz'])
    if(os.path.exists(compressed_file)):
        os.remove(compressed_file)

    xz_compressor_filter = [
        {"id": lzma.FILTER_LZMA2, "preset": 6, "dict_size": 64*1024},
    ]
    with open(in_file, 'rb') as src_f:
        data = src_f.read()
        with lzma.open(compressed_file, "wb", format=lzma.FORMAT_XZ, check=lzma.CHECK_CRC32, filters=xz_compressor_filter) as f:
            f.write(data)
            f.close()
    
    if not os.path.exists(os.path.join(store_directory, os.path.split(compressed_file)[1])):
        shutil.copy(compressed_file, store_directory)
        print('copy xz file done')

def secure_boot_sign(sign_key, in_file, out_file):
    ret = subprocess.call('espsecure.py sign_data --version 2 --keyfile {} --output {} {}'.format(sign_key, out_file, in_file), shell = True)
    if ret:
        raise Exception('sign failed')

def get_app_name():
    with open('flasher_args.json') as f:
        try:
            flasher_args = json.load(f)
            return flasher_args['app']['file']
        except Exception as e:
            print(e)

    return ''

def get_script_version():
    return SCRIPT_VERSION

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-hv', '--header_ver', nargs='?', choices = ['v1', 'v2', 'v3'], 
            default='v3', help='the version of the packed file header [default:v3]')
    parser.add_argument('-c', '--compress_type', nargs= '?', choices = ['none', 'xz'], 
            default='xz', help='compressed type [default:xz]')
    parser.add_argument('-i', '--in_file', nargs = '?', 
            default='', help='the new app firmware')
    parser.add_argument('--sign_key', nargs = '?', 
            default='', help='the sign key used for secure boot')
    parser.add_argument('-fv', '--fw_ver', nargs='?', 
            default='', help='the version of the compressed data(this field is deprecated in v3)')
    parser.add_argument('--add_app_header', action="store_true", help='add app header to use native esp_ota_* & esp_https_ota_* APIs')
    parser.add_argument('-v', '--version', action='version', version=get_script_version(), help='the version of the script')
    
    args = parser.parse_args()

    compress_type = args.compress_type
    firmware_ver = args.fw_ver
    src_file = args.in_file
    sign_key = args.sign_key
    header_ver = args.header_ver
    add_app_header = args.add_app_header

    if src_file == '':
        origin_app_name = get_app_name()
        if(origin_app_name == ''):
            print('get origin app name fail')
            return
        
        if os.path.exists(origin_app_name):
            src_file = origin_app_name
        else:
            print('origin app.bin not found')
            return
    
    print('src file is: {}'.format(src_file))

    # rebuild the cpmpressed_app directroy
    cpmoressed_app_directory = 'custom_ota_binaries'
    if os.path.exists(cpmoressed_app_directory):
        shutil.rmtree(cpmoressed_app_directory)
    
    os.mkdir(cpmoressed_app_directory)
    print('The compressed file will store in {}'.format(cpmoressed_app_directory))

    #step1: compress
    if compress_type == 'xz':
        xz_compress(cpmoressed_app_directory, os.path.abspath(src_file))

        origin_app_name = os.path.split(src_file)[1]

        compressed_file_name = ''.join([origin_app_name, '.xz'])
        compressed_file = os.path.join(cpmoressed_app_directory, compressed_file_name)
    else:
        compressed_file = ''.join(src_file)
    
    print('compressed file is: {}'.format(compressed_file))

    #step2: packet the compressed image header
    with open(src_file, 'rb') as s_f:
        src_image_header = bytearray(s_f.read(ORIGIN_APP_IMAGE_HEADER_LEN))
        src_image_header[1] = 0x00

    packed_file = ''.join([compressed_file,'.packed'])
    with open(compressed_file, 'rb') as src_f:
        data = src_f.read()
        f_len = src_f.tell()
        # magic number
        bin_data = struct.pack('4s', b'ESP')
        # header version
        bin_data += struct.pack('B', header_version[header_ver])
        # Compress type
        bin_data += struct.pack('B', binary_compress_type[compress_type])
        print('compressed type: {}'.format(binary_compress_type[compress_type]))
        # in header v1/v2, there is a field "Encryption type", this field has been deprecated in v3
        if (header_version[header_ver] < 3):
            bin_data += struct.pack('B', 0)
            # Reserved
            bin_data += struct.pack('?', 0)
            # Firmware version
            bin_data += struct.pack('32s', firmware_ver.encode())
        else:
            # Reserved
            bin_data += struct.pack('10s', b'0')
        # The length of the compressed data
        bin_data += struct.pack('<I', f_len)
        print('compressed data len: {}'.format(f_len))
        # The MD5 for the compressed data
        if (header_version[header_ver] < 3):
            bin_data += struct.pack('32s', hashlib.md5(data).digest())
            if (header_version[header_ver] == 2):
                # Todo, if it's diff OTA, write base app check data len
                bin_data += struct.pack('<I', 0)
                # Todo, if it's diff OTA, write base app crc32 checksum
                bin_data += struct.pack('<I', 0)
        else:
            bin_data += struct.pack('16s', hashlib.md5(data).digest())
        # The CRC32 for the header
        bin_data += struct.pack('<I', binascii.crc32(bin_data, 0x0))
        
        # write compressed data
        bin_data += data
        with open(packed_file, 'wb') as dst_f:
            # write compressed image header and compressed dada
            dst_f.write(bin_data)
    
    print('packed file is: {}'.format(packed_file))

    #step3: if need sign, then sign the packed image
    if sign_key != '':
        signed_file = ''.join([packed_file,'.signed'])
        secure_boot_sign(sign_key, packed_file, signed_file)
        print('signed_file is: {}'.format(signed_file))
    else:
        signed_file = ''.join(packed_file)
        
    if (header_version[header_ver] == 3) and add_app_header:
        with open(signed_file, 'rb+') as src_f:
            packed_data = src_f.read()
            src_f.seek(0)
            # write origin app image header
            src_f.write(src_image_header)
            # write compressed image header and compressed dada
            src_f.write(packed_data)
            print('app image header has been added')

if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        print(e)
        sys.exit(2)
