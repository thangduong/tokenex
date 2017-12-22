from ctypes import *
import os

script_dir = os.path.dirname(os.path.abspath(__file__))

if os.name=='nt':
	tok_so = cdll.LoadLibrary(os.path.join(script_dir,'tokenizer.dll'))
else:
	tok_so = cdll.LoadLibrary(os.path.join(script_dir,'tokenizer_so.so'))
tok_so.LoadTokenizer.argtypes = []
tok_so.LoadTokenizer.restype = c_void_p
tok_so.TokenizeString.argtypes = [c_void_p, c_char_p, c_bool]
tok_so.TokenizeString.restype = c_void_p
tok_so.NextToken.argtypes = [c_void_p, POINTER(c_int), POINTER(c_int), POINTER(c_int)]
tok_so.NextToken.restype = c_char_p
tok_so.FreeTokenizedResult.argtypes = [c_void_p]
tok_so.LoadDefaultConfig.argtypes = [c_void_p, c_int]
tok_so.UnloadTokenizer.argtypes = [c_void_p]

class Tokenizer:
	def __init__(self, config = 0):
		"""
		Constructor
		@param config: config information
			0 = default standard with regex.
			1 = default keep all with regex.  keep the ' ', but convert numbers to <int>.
			2 = default standard with no regex.
			3 = default keep all with no regex.  keep everything unaltered.  just split the string up.
			<a string> = path to config file.  this is supported yet
		"""
		self._tokenizer = tok_so.LoadTokenizer()
		tok_so.LoadDefaultConfig(self._tokenizer, c_int(config))

	def tokenize(self, string, translit=True):
		"""
		Simple tokenization of a string using the tokenizer.
		:param string: the string to tokenize
		:param translit: True to do utf-8 to ASCII translit.  False otherwise.
		:return: a list of tokens.  If the tokenizer's created with config=3, then ''.join(result) should be the original
		string.
		"""
		input_string = c_char_p(string.encode('utf-8', errors="ignore"))
		tokenizer_result = tok_so.TokenizeString(self._tokenizer, input_string, translit)
		start = c_int()
		len = c_int()
		type = c_int()
		done = False
		result = []
		while (not done):
			ctoken = tok_so.NextToken(tokenizer_result, byref(start), byref(len), byref(type))
			if ctoken is not None:
				token = c_char_p(ctoken).value.decode('utf-8', errors="ignore")
				result.append(token)
			else:
				done = True
		tok_so.FreeTokenizedResult(tokenizer_result)
		return result

	def tokenize_ex(self, string, translit=True):
		"""
		Tokneize a string as the tokenize(.) function, but this function returns more information.
		:param string: string to tokenize
		:param translit: True to translit.  False to not translit.
		:return: A list of list.  Each element is a 4 element list:
		    [string token, start index in string, end index in string, type of token]
		"""
		input_string = c_char_p(string.encode('utf-8', errors="ignore"))
		tokenizer_result = tok_so.TokenizeString(self._tokenizer, input_string, translit)
		start = c_int()
		len = c_int()
		type = c_int()
		done = False
		result = []
		while (not done):
			ctoken = tok_so.NextToken(tokenizer_result, byref(start), byref(len), byref(type))
			if ctoken is not None:
				token = [c_char_p(ctoken).value.decode('utf-8', errors="ignore"), start.value, len.value, type.value]
				result.append(token)
			else:
				done = True
		tok_so.FreeTokenizedResult(tokenizer_result)
		return result

	def cleanup(self):
		tok_so.UnloadTokenizer(self._tokenizer)

	def __enter__(self):
		return self

	def __exit__(self, exc_type, exc_value, traceback):
		self.cleanup()
