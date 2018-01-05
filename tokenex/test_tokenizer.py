# code to test tokenizer for specific things
#
import unittest
from tokenizer import Tokenizer

class TestTokenizer(unittest.TestCase):
	def setUp(self):
		pass

	def test_py_cases(self):
		tok = Tokenizer()
		without_original = tok.tokenize("10 is ten", regex_keep_original=False)
		with_original = tok.tokenize("10 is ten", regex_keep_original=True)
		self.assertEqual(' '.join(without_original), "<int> is ten")
		self.assertEqual(' '.join(with_original), "<int>|10 is ten")

	def test_correctness(self):
		test_strings = [
			["today      is monday. hello1920s world tomorrow is the 10th of april 1920,and it will rain",
		    "today is monday . hello1920s world tomorrow is the <ordinal>|10th of april <int>|1920 , and it will rain"
			],
			[
				"F.D.R. was a great president in the 1930s , and A.I.G was an insurance company. 1929 was a bad year. bob's cat is black. don't do it.",
				"F.D.R. was a great president in the <decade-year>|1930s , and A.I.G was an insurance company . <int>|1929 was a bad year . bob 's cat is black . do n't do it ."
			],
			[
				'\'$`:!%^)(][}{@#~-.";,™€°?*|…=+&/\—––’ʼ“”‘′¶″·¢⁄><−•·',
				'\' $ \' : ! % ^ ) ( ] [ } { @ # ~ - . " ; , (tm) € ° ? * | ... = + & / \ ------ \' \' " " \' \' ¶ " · ¢ ⁄ > < − • ·',
			],
			[
			 'The music was better in the 1980s',
			 'The music was better in the <decade-year>|1980s'
			 ],
			[
				'The music was better in the 80s',
				'The music was better in the <decade>|80s'
			],
			[
				'20 people went to the market',
				'<int>|20 people went to the market'
			],
			[
				'You can e-mail me at thang@quantee.com or visit my website at http://www.quantee.com',
				'You can e-mail me at <email>|thang@quantee.com or visit my website at <url>|http://www.quantee.com'
			],
		]
		tok = Tokenizer()
		for test_case in test_strings:
			tokens = tok.tokenize(test_case[0],regex_keep_original=True)
			self.assertEqual(' '.join(tokens), test_case[1])

if __name__ == "__main__":
	unittest.main()

