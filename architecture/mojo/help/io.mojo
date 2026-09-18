from conf import *

def wait_stdin() -> S32:
    try:
        var _ =  input()
        return 0
    except e:
        print(e)
        return 1
