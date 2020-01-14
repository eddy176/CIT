"""
Do Not Edit this file. You may and are encouraged to look at it for reference.
"""

import sys
if sys.version_info.major != 3:
    print('You must use Python 3.x version to run this unit test')
    sys.exit(1)

import unittest

import main


class TestGetUserFloat(unittest.TestCase):
    def input_replacement(self, prompt):
        self.assertFalse(self.too_many_inputs)
        self.input_given_prompt = prompt
        r = self.input_response_list[self.input_response_index]
        self.input_response_index += 1
        if self.input_response_index >= len(self.input_response_list):
            self.input_response_index = 0
            self.too_many_inputs = True
        return r


    def print_replacement(self, *args, **kargs):
        return


    def setUp(self):
        self.too_many_inputs = False
        self.input_given_prompt = None
        self.input_response_index = 0
        self.input_response_list = [""]
        main.input = self.input_replacement
        main.print = self.print_replacement
        return

    def test001_getUserFloatExists(self):
        self.assertTrue('getUserFloat' in dir(main),
                        'Function "getUserFloat" is not defined, check your spelling')
        return

    def test002_getUserFloatSendsCorrectPrompt(self):
        from main import getUserFloat
        expected_prompt = "HELLO"
        expected_response = "1.7"
        self.input_response_list = [expected_response]
        actual_response = getUserFloat(expected_prompt)
        self.assertEqual(expected_prompt, self.input_given_prompt)
        return

    def test003_getUserFloatGetsInput(self):
        from main import getUserFloat
        expected_prompt = "HELLO"
        expected_response = "1"
        self.input_response_list = [expected_response]
        actual_response = getUserFloat(expected_prompt)
        self.assertTrue(type(actual_response) is float)
        self.assertEqual(1.0, actual_response)
        return

    def test004_getUserFloatStripsWhitespace(self):
        from main import getUserFloat
        expected_prompt = "HELLO"
        expected_response = "1.7"
        self.input_response_list = [" \t\n" + expected_response + " \t\n"]
        actual_response = getUserFloat(expected_prompt)
        self.assertTrue(type(actual_response) is float)
        self.assertEqual(float(expected_response), actual_response)
        return

    def test005_getUserFloatBadInputCheck(self):
        from main import getUserFloat
        expected_prompt = "HELLO"
        expected_response = "7.6"
        self.input_response_list = ["zero", "-1.7", "0", "0.0", "-20.0", "", "sixteen", expected_response]
        actual_response = getUserFloat(expected_prompt)
        self.assertTrue(type(actual_response) is float)
        self.assertEqual(float(expected_response), actual_response,
            'Your repsonse (%s) did not equal the expected response (%s)' % (actual_response, expected_response))
        return

    def test006_getUserFloatIgnoresBlankLines(self):
        from main import getUserFloat
        expected_prompt = "HELLO"
        expected_response = "10"
        self.input_response_list = ["", "0.0", "hello", "-1.7", "\n", " \t\n" + expected_response + " \t\n"]
        actual_response = getUserFloat(expected_prompt)
        self.assertTrue(type(actual_response) is float)
        self.assertEqual(10.0, actual_response)
        return


if __name__ == '__main__':
    unittest.main()