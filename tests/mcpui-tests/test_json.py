"""McpUI responses must stay valid JSON whatever the labels contain, and
every control must get its own tool name.

Run with: python3 -m unittest discover -s tests/mcpui-tests -v
"""
import json
import os
from pathlib import Path
import re
import shlex
import subprocess
import tempfile
import unittest


TEST_DIR = Path(__file__).resolve().parent
ROOT = TEST_DIR.parents[1]
SERVER_NAME = 'Root "main" C:\\dsp\\'
ASCII_LABELS = ['path\\', 'Gain "dB"\tleft  right', 'two  spaces']
SLIDER_COUNT = 7


class JsonTests(unittest.TestCase):
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
                   str(TEST_DIR / "json_server.cpp"), "-o", str(server)],
                # An empty entry in CPLUS_INCLUDE_PATH searches the current directory,
                # where the repository root's 'version' script would hide <version>
                cwd=str(TEST_DIR), check=True,
            )
            cls.servers.append(server)

    def session(self, server, lines):
        """Send raw request lines, return one parsed response per output line."""
        output = subprocess.run(
            [str(server)], input="".join(line + "\n" for line in lines),
            text=True, encoding="utf-8", capture_output=True, check=True,
        ).stdout
        responses = []
        for line in output.splitlines():
            try:
                responses.append(json.loads(line))
            except json.JSONDecodeError as error:
                self.fail("invalid JSON response (%s): %r" % (error, line))
        self.assertEqual(len(responses), len(lines))
        return responses

    @staticmethod
    def request(method, **params):
        return json.dumps({"jsonrpc": "2.0", "id": "1", "method": method, "params": params},
                          ensure_ascii=False)

    def tools(self, server):
        return self.session(server, [self.request("tools/list")])[0]["result"]["tools"]

    def test_initialize_escapes_server_name(self):
        for server in self.servers:
            with self.subTest(char_mode=server.name):
                result = self.session(server, [self.request("initialize")])[0]["result"]
                self.assertEqual(result["serverInfo"]["name"], SERVER_NAME)

    def test_descriptions_keep_labels(self):
        for server in self.servers:
            with self.subTest(char_mode=server.name):
                descriptions = [tool["description"] for tool in self.tools(server)]
                for label in ASCII_LABELS:
                    prefix = "Control " + label + " (" + SERVER_NAME + "): range ["
                    self.assertTrue(any(d.startswith(prefix) for d in descriptions),
                                    "no description starts with %r in %r" % (prefix, descriptions))

    def test_tool_names_are_unique(self):
        for server in self.servers:
            with self.subTest(char_mode=server.name):
                names = [tool["name"] for tool in self.tools(server)]
                self.assertEqual(len(names), SLIDER_COUNT, names)
                self.assertEqual(len(set(names)), SLIDER_COUNT, names)
                for name in names:
                    self.assertRegex(name, r"^[A-Za-z0-9_]{1,50}$")

    def test_each_tool_drives_its_own_control(self):
        for server in self.servers:
            with self.subTest(char_mode=server.name):
                names = [tool["name"] for tool in self.tools(server)]
                # Each slider has a distinct maximum: a large value is clamped to it
                calls = [self.request("tools/call", name=name, arguments={"value": "100"})
                         for name in names]
                maxima = set()
                for response in self.session(server, calls):
                    text = response["result"]["content"][0]["text"]
                    maxima.add(float(re.search(r" set to (\S+)$", text).group(1)))
                self.assertEqual(maxima, set(float(m) for m in range(1, SLIDER_COUNT + 1)))

    def test_call_confirmation_keeps_label(self):
        for server in self.servers:
            with self.subTest(char_mode=server.name):
                tool = next(t for t in self.tools(server)
                            if t["description"].startswith("Control Gain"))
                response = self.session(server, [self.request(
                    "tools/call", name=tool["name"], arguments={"value": "1"})])[0]
                self.assertEqual(response["result"]["content"][0]["text"],
                                 ASCII_LABELS[1] + " (" + SERVER_NAME + ") set to 1.000000")

    def test_cleaner_tracks_escaped_backslashes(self):
        # "a\\" ends with an escaped backslash: the next string must keep its double spaces
        value = '{"first": "a\\\\", "second": "two  spaces"}'
        for server in self.servers:
            with self.subTest(char_mode=server.name):
                output = subprocess.run(
                    [str(server), "--clean"], input=value, text=True,
                    encoding="utf-8", capture_output=True, check=True,
                ).stdout
                self.assertEqual(output, value)
                self.assertEqual(json.loads(output)["second"], "two  spaces")

    def test_error_message_is_valid_json(self):
        # The request parser stops the tool name at the escaped quote: "a\"
        line = '{"jsonrpc": "2.0", "id": "1", "method": "tools/call", ' \
               '"params": {"name": "a\\"b", "arguments": {"value": "1"}}}'
        for server in self.servers:
            with self.subTest(char_mode=server.name):
                response = self.session(server, [line])[0]
                self.assertEqual(response["error"]["code"], -32602)


if __name__ == "__main__":
    unittest.main()
