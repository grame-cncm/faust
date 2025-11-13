'''
Steps to run these cases:
- Build
  - . ${IDF_PATH}/export.sh
  - pip install idf_build_apps
  - python tools/build_apps.py tools/cmake_utilities/test_apps -t esp32s2
- Test
  - pip install -r tools/requirements/requirement.pytest.txt
  - pytest tools/cmake_utilities/test_apps --target esp32s2
'''

import pytest
from pytest_embedded import Dut

@pytest.mark.target('esp32s3')
@pytest.mark.env('generic')
def test_cmake_utilities(dut: Dut)-> None:
    dut.expect_exact('Press ENTER to see the list of tests.')
    dut.write('*')
    dut.expect_unity_test_output(timeout = 1000)
