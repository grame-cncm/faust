import json
import os
from pathlib import Path
import shlex
import subprocess
import tempfile
import unittest


TEST_DIR = Path(__file__).resolve().parent
ROOT = TEST_DIR.parents[1]
SERVER_NAME = "Synthé 音 🎵"
LABEL = "Fréquence"


class Utf8Tests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.temp_dir = tempfile.TemporaryDirectory()
        cls.addClassCleanup(cls.temp_dir.cleanup)
        cls.servers = []
        for mode in ("signed", "unsigned"):
            server = Path(cls.temp_dir.name) / mode
            subprocess.run(
                shlex.split(os.environ.get("CXX", "c++"))
                + ["-std=c++14", "-Wall", "-Wextra", "-Wno-unused-parameter",
                   "-f" + mode + "-char", "-I" + str(ROOT / "architecture"),
                   str(TEST_DIR / "utf8_server.cpp"), "-o", str(server)],
                check=True,
            )
            cls.servers.append(server)

    def request(self, server, method, **params):
        request = {"jsonrpc": "2.0", "id": "1", "method": method, "params": params}
        output = subprocess.run(
            [str(server)], input=json.dumps(request) + "\n",
            text=True, encoding="utf-8", capture_output=True, check=True,
        ).stdout
        return json.loads(output)["result"]

    def test_cleaner_preserves_utf8(self):
        value = json.dumps({"text": "é 音 🎵", "ascii": "unchanged"}, ensure_ascii=False)
        for server in self.servers:
            with self.subTest(char_mode=server.name):
                output = subprocess.run(
                    [str(server), "--clean"], input=value, text=True,
                    encoding="utf-8", capture_output=True, check=True,
                ).stdout
                self.assertEqual(output, value)

    def test_cleaner_still_removes_ascii_controls(self):
        for server in self.servers:
            with self.subTest(char_mode=server.name):
                output = subprocess.run(
                    [str(server), "--clean"], input='\n{  "text": "a\x01b\x7fc" }\r\n',
                    text=True, encoding="utf-8", capture_output=True, check=True,
                ).stdout
                self.assertEqual(output, '{ "text": "abc" }')

    def test_initialize_preserves_server_name(self):
        for server in self.servers:
            with self.subTest(char_mode=server.name):
                result = self.request(server, "initialize")
                self.assertEqual(result["serverInfo"]["name"], SERVER_NAME)

    def test_tools_list_preserves_description(self):
        for server in self.servers:
            with self.subTest(char_mode=server.name):
                tool = self.request(server, "tools/list")["tools"][0]
                self.assertTrue(tool["description"].startswith(
                    "Control " + LABEL + " (" + SERVER_NAME + "): range ["))

    def test_tool_call_preserves_confirmation(self):
        for server in self.servers:
            with self.subTest(char_mode=server.name):
                tool = self.request(server, "tools/list")["tools"][0]
                result = self.request(server, "tools/call", name=tool["name"],
                                      arguments={"value": "0.75"})
                self.assertEqual(result["content"][0]["text"],
                                 LABEL + " (" + SERVER_NAME + ") set to 0.750000")


if __name__ == "__main__":
    unittest.main()
