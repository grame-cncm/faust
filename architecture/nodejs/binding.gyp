{
    'targets': [
    {
        'target_name': 'faust',
        'include_dirs': [ '/usr/local/include' ],
        'cflags_cc!': [ '-fno-rtti','-fno-exceptions' ],
        'conditions': [
            ['OS=="mac"', {
                'xcode_settings': {
                'GCC_ENABLE_CPP_RTTI': 'YES',
                'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
                }
            }]
        ],
        'cflags': [ '__CFLAGS__' ],
        'libraries': [ '-L/usr/local/lib -L/opt/local/lib __LIBFLAGS__' ],
        'sources': [ 'faust.cpp','DspFaust.cpp','DspFaustNode.cpp' ]
    }]
}