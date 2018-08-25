"""
Do Not Edit this file. You may and are encouraged to look at it for reference.
"""

import unittest
import isbn_index

class test_getUserChoice( unittest.TestCase ):

    def input_replacement( self, prompt ):
        self.assertFalse( self.too_many_inputs )
        self.input_given_prompt = prompt
        r = self.input_response_list[ self.input_response_index ]
        self.input_response_index += 1
        if self.input_response_index >= len( self.input_response_list ):
            self.input_response_i6ndex = 0
            self.too_many_inputs = True
        return r
    
    def setUp(self):
        
        self.too_many_inputs = False
        self.input_given_prompt = None
        self.input_response_index = 0
        self.input_response_list = [ "" ]
        isbn_index.input = self.input_replacement

        return

    def tearDown(self):
        return
    
    def test001_getUserChoiceExists(self):
        self.assertTrue('getUserChoice' in dir( isbn_index ),
                        'Function "getUserChoice" is not defined, check your spelling')
        return
    
    def test002_getUserChoiceSendsCorrectPrompt(self):
        expected_prompt = "HELLO"
        expected_response = "WORLD"
        self.input_response_list = [ expected_response ]
        actual_response = isbn_index.getUserChoice( expected_prompt )
        self.assertEqual( self.input_given_prompt, expected_prompt )
        return

    def test003_getUserChoiceGetsInput(self):
        expected_prompt = "HELLO"
        expected_response = "WORLD"
        self.input_response_list = [ expected_response ]
        actual_response = isbn_index.getUserChoice( expected_prompt )
        self.assertEqual( actual_response, expected_response )
        return

    def test004_getUserChoiceStripsWhitespace(self):
        expected_prompt = "HELLO"
        expected_response = "WORLD"
        self.input_response_list = [ " \t\n" + expected_response + " \t\n" ]
        actual_response = isbn_index.getUserChoice( expected_prompt )
        self.assertEqual( actual_response, expected_response )
        return
    
    def test005_getUserChoiceIgnoresBlankLines(self):
        expected_prompt = "HELLO"
        expected_response = "WORLD"
        self.input_response_list = [ "", "\n", " \t\n" + expected_response + " \t\n" ]
        actual_response = isbn_index.getUserChoice( expected_prompt )
        self.assertEqual( actual_response, expected_response )
        return


if __name__ == '__main__':
    unittest.main()
