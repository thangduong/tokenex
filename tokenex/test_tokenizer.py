# code to test tokenizer for specific things
#
import unittest
from tokenizer import Tokenizer

class TestTokenizer(unittest.TestCase):
	def setUp(self):
		pass

	def test_correctness(self):
		test_strings = [
			["today      is monday. hello1920s world tomorrow is the 10th of april 1920,and it will rain",
		    "today is monday . hello1920s world tomorrow is the <ordinal> of april <int> , and it will rain"
			],
			[
				'\'$`:!%^)(][}{@#~-.";,™€°?*|…=+&/\—––’ʼ“”‘′¶″·¢⁄><−•·',
				'\' $ \' : ! % ^ ) ( ] [ } { @ # ~ - . " ; , (tm) € ° ? * | ... = + & / \ ------ \' \' " " \' \' ¶ " · ¢ ⁄ > < − • ·',
			],
			[
			 'The music was better in the 1980s',
			 'The music was better in the <decade-year>'
			 ],
			[
				'The music was better in the 80s',
				'The music was better in the <decade>'
			],
			[
				'20 people went to the market',
				'<int> people went to the market'
			],
			[
				'You can e-mail me at thang@quantee.com or visit my website at http://www.quantee.com',
				'You can e-mail me at <email> or visit my website at <url>'
			],
		]
		tok = Tokenizer()
		for test_case in test_strings:
			tokens = tok.tokenize(test_case[0])
			self.assertEqual(' '.join(tokens), test_case[1])

if __name__ == "__main__":
	unittest.main()

