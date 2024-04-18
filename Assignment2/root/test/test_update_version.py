import unittest
from unittest.mock import patch
from update_version import update_file, update_sconstruct, update_version
import os

class TestUpdateVersion(unittest.TestCase):
    def test_update_file(self):
        with open('test_file.txt', 'w') as file:
            file.write('ADLMSDK_VERSION_POINT=123\n')
        update_file('test_file.txt', r'ADLMSDK_VERSION_POINT=\d+', 'ADLMSDK_VERSION_POINT=456')
        with open('test_file.txt', 'r') as file:
            content = file.read()
        os.remove('test_file.txt')
        self.assertEqual(content, 'ADLMSDK_VERSION_POINT=456\n')

    @patch.dict(os.environ, {'BuildNum': '789', 'SourcePath': '/some/path'})
    @patch('update_version.update_sconstruct')
    @patch('update_version.update_version')
    def test_main(self, mock_update_version, mock_update_sconstruct):
        import update_version
        update_version.main()
        mock_update_sconstruct.assert_called_once_with('789', '/some/path')
        mock_update_version.assert_called_once_with('789', '/some/path')

if __name__ == '__main__':
    unittest.main()
