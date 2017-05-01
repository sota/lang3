
#line 1 "lexer.rl"
/*
vim: syntax=ragel
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <exception>
#include <stdexcept>

#include "lexer.h"
#include "ascii.h"

using std::cerr;
using std::cout;
using std::cin;
using std::endl;
using std::copy;

#define T(t,i,v) {i,v},
static std::map<long, const char *> TokenMap = {
	ASCII
	TOKENS
};
#undef T

inline void write(const char *data) {
	cout << data;
}

inline void write(const char c) {
	cout << c;
}

inline void write(const char *data, int len) {
	cout.write(data, len);
}


static const char _sast_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1,
	3, 1, 5, 1, 6, 1, 7, 1,
	8, 1, 9, 1, 13, 1, 14, 1,
	15, 1, 16, 1, 17, 1, 18, 1,
	19, 1, 20, 1, 21, 1, 22, 1,
	23, 2, 0, 4, 2, 0, 12, 2,
	3, 10, 2, 3, 11, 0
};

static const char _sast_key_offsets[] = {
	0, 0, 2, 5, 8, 10, 13, 30,
	43, 44, 47, 62, 64, 65, 67, 68,
	0
};

static const char _sast_trans_keys[] = {
	48, 57, 10, 13, 35, 10, 13, 35,
	10, 13, 10, 13, 34, 9, 10, 13,
	32, 34, 35, 39, 40, 41, 46, 59,
	91, 93, 123, 125, 48, 57, 10, 13,
	32, 46, 59, 91, 93, 123, 125, 34,
	35, 39, 41, 13, 10, 13, 32, 10,
	13, 32, 46, 59, 91, 93, 123, 125,
	34, 35, 39, 41, 48, 57, 48, 57,
	35, 10, 13, 13, 34, 0
};

static const char _sast_single_lengths[] = {
	0, 0, 3, 3, 2, 3, 15, 9,
	1, 3, 9, 0, 1, 2, 1, 1,
	0
};

static const char _sast_range_lengths[] = {
	0, 1, 0, 0, 0, 0, 1, 2,
	0, 0, 3, 1, 0, 0, 0, 0,
	0
};

static const char _sast_index_offsets[] = {
	0, 0, 2, 6, 10, 13, 17, 34,
	46, 48, 52, 65, 67, 69, 72, 74,
	0
};

static const char _sast_trans_cond_spaces[] = {
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, 0
};

static const char _sast_trans_offsets[] = {
	0, 1, 2, 3, 4, 5, 6, 7,
	8, 9, 10, 11, 12, 13, 14, 15,
	16, 17, 18, 19, 20, 21, 22, 23,
	24, 25, 26, 27, 28, 29, 30, 31,
	32, 33, 34, 35, 36, 37, 38, 39,
	40, 41, 42, 43, 44, 45, 46, 47,
	48, 49, 50, 51, 52, 53, 54, 55,
	56, 57, 58, 59, 60, 61, 62, 63,
	64, 65, 66, 67, 68, 69, 70, 71,
	72, 73, 74, 75, 76, 77, 78, 79,
	80, 81, 82, 83, 84, 0
};

static const char _sast_trans_lengths[] = {
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 0
};

static const char _sast_cond_keys[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0
};

static const char _sast_cond_targs[] = {
	11, 6, 3, 3, 13, 3, 3, 3,
	12, 3, 14, 12, 4, 5, 5, 15,
	5, 7, 8, 6, 9, 6, 6, 6,
	6, 6, 6, 6, 6, 6, 6, 6,
	10, 7, 6, 6, 6, 6, 6, 6,
	6, 6, 6, 6, 6, 7, 6, 6,
	8, 6, 9, 6, 6, 6, 6, 1,
	6, 6, 6, 6, 6, 6, 6, 10,
	7, 11, 6, 2, 0, 14, 12, 4,
	12, 12, 5, 0, 6, 12, 6, 6,
	6, 6, 6, 12, 12, 0
};

static const char _sast_cond_actions[] = {
	0, 37, 1, 1, 7, 0, 1, 1,
	9, 0, 1, 41, 0, 1, 1, 17,
	0, 47, 1, 44, 0, 21, 19, 27,
	23, 25, 29, 29, 23, 25, 23, 25,
	7, 50, 39, 39, 39, 39, 39, 39,
	39, 39, 39, 39, 39, 50, 44, 33,
	1, 44, 0, 31, 35, 35, 35, 0,
	35, 35, 35, 35, 35, 35, 35, 7,
	50, 0, 35, 0, 0, 1, 41, 0,
	41, 11, 0, 0, 37, 15, 39, 33,
	31, 35, 35, 13, 11, 0
};

static const char _sast_to_state_actions[] = {
	0, 0, 0, 0, 0, 0, 3, 0,
	0, 0, 0, 0, 3, 0, 0, 3,
	0
};

static const char _sast_from_state_actions[] = {
	0, 0, 0, 0, 0, 0, 5, 0,
	0, 0, 0, 0, 5, 0, 0, 5,
	0
};

static const char _sast_eof_trans_indexed[] = {
	0, 9, 0, 0, 28, 0, 0, 17,
	18, 19, 20, 20, 0, 30, 31, 0,
	0
};

static const char _sast_eof_trans_direct[] = {
	0, 77, 0, 0, 78, 0, 0, 79,
	80, 81, 82, 83, 0, 84, 85, 0,
	0
};

static const char _sast_nfa_targs[] = {
	0, 0
};

static const char _sast_nfa_offsets[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0
};

static const char _sast_nfa_push_actions[] = {
	0, 0
};

static const char _sast_nfa_pop_trans[] = {
	0, 0
};

static const int sast_start = 6;
static const int sast_error = 0;

static const int sast_en_commenter = 12;
static const int sast_en_string = 15;
static const int sast_en_body = 6;


#line 130 "lexer.rl"


class Lexer {
	char const* const source;
	char const* const pe;
	char const* const eof;
	char const* p;
	char const* ts;
	char const* te;
	int stack[1];
	int cs;
	int act;
	int top;
	int nesting;
	std::vector<const char *> newlines;
	std::vector<CToken> tokens;
	
	public:
	Lexer(char const* const source)
	: source(source)
	, pe(source + strlen(source))
	, eof(source + strlen(source))
	, p(source)
	, nesting(0) {
		
		{
			cs = (int)sast_start;
			ts = 0;
			te = 0;
			act = 0;
		}
		
		#line 155 "lexer.rl"
		
		//pretend newline before start of file
		newlines.push_back(source-1);
	}
	
	~Lexer() {
		newlines.clear();
		tokens.clear();
	}
	
	void AddNewline(const char *pchar) {
		if (pchar > newlines.back())
		newlines.push_back(pchar);
		else
		printf("UNEXPECTED BEHAVIOR!!!\n");
	}
	
	const char * Newline(const char *pchar) {
		for (unsigned i = newlines.size(); i-- > 0;) {
			if (pchar > newlines[i])
			return newlines[i];
		}
		return 0;
	}
	
	long Line(const char *pchar) {
		for (unsigned i = newlines.size(); i-- > 0;) {
			if (pchar > newlines[i])
			return i + 1;
		}
		return 0;
	}
	
	long Pos(const char *pchar) {
		const char *nl = Newline(pchar);
		if (nl)
		return pchar - nl;
		return 0;
	}
	
	void Token(long kind, long trim=0) {
		tokens.push_back({
			ts - source + trim,
			te - source - trim,
			kind,
			Line(ts),
			Pos(ts)});
	}
	
	void Token(long start, long end, long kind, long line, long pos, long skip) {
		tokens.push_back({
			start,
			end,
			kind,
			line,
			pos,
			skip});
	}
	
	long Scan(CToken **tokens) {
		Token(0, 0, '{', 0, 0, 0);
			
			{
				int _klen;
				unsigned int _trans = 0;
				unsigned int _cond = 0;
				const char *_acts;
				unsigned int _nacts;
				const char *_keys;
				const char *_ckeys;
				int _cpc;
				{
					
					if ( p == pe )
					goto _test_eof;
					if ( cs == 0 )
					goto _out;
					_resume:  {
						_acts = ( _sast_actions + (_sast_from_state_actions[cs]));
						_nacts = (unsigned int)(*( _acts));
						_acts += 1;
						while ( _nacts > 0 ) {
							switch ( (*( _acts)) ) {
								case 2:  {
									{
										#line 1 "NONE"
										{ts = p;}}
									break; }
							}
							_nacts -= 1;
							_acts += 1;
						}
						
						_keys = ( _sast_trans_keys + (_sast_key_offsets[cs]));
						_trans = (unsigned int)_sast_index_offsets[cs];
						
						_klen = (int)_sast_single_lengths[cs];
						if ( _klen > 0 ) {
							const char *_lower;
							const char *_mid;
							const char *_upper;
							_lower = _keys;
							_upper = _keys + _klen - 1;
							while ( 1 ) {
								if ( _upper < _lower )
								break;
								
								_mid = _lower + ((_upper-_lower) >> 1);
								if ( ( (*( p))) < (*( _mid)) )
								_upper = _mid - 1;
								else if ( ( (*( p))) > (*( _mid)) )
								_lower = _mid + 1;
								else {
									_trans += (unsigned int)(_mid - _keys);
									goto _match;
								}
							}
							_keys += _klen;
							_trans += (unsigned int)_klen;
						}
						
						_klen = (int)_sast_range_lengths[cs];
						if ( _klen > 0 ) {
							const char *_lower;
							const char *_mid;
							const char *_upper;
							_lower = _keys;
							_upper = _keys + (_klen<<1) - 2;
							while ( 1 ) {
								if ( _upper < _lower )
								break;
								
								_mid = _lower + (((_upper-_lower) >> 1) & ~1);
								if ( ( (*( p))) < (*( _mid)) )
								_upper = _mid - 2;
								else if ( ( (*( p))) > (*( _mid + 1)) )
								_lower = _mid + 2;
								else {
									_trans += (unsigned int)((_mid - _keys)>>1);
									goto _match;
								}
							}
							_trans += (unsigned int)_klen;
						}
						
					}
					_match:  {
						_ckeys = ( _sast_cond_keys + (_sast_trans_offsets[_trans]));
						_klen = (int)_sast_trans_lengths[_trans];
						_cond = (unsigned int)_sast_trans_offsets[_trans];
						
						_cpc = 0;
						{
							const char *_lower;
							const char *_mid;
							const char *_upper;
							_lower = _ckeys;
							_upper = _ckeys + _klen - 1;
							while ( 1 ) {
								if ( _upper < _lower )
								break;
								
								_mid = _lower + ((_upper-_lower) >> 1);
								if ( _cpc < (int)(*( _mid)) )
								_upper = _mid - 1;
								else if ( _cpc > (int)(*( _mid)) )
								_lower = _mid + 1;
								else {
									_cond += (unsigned int)(_mid - _ckeys);
									goto _match_cond;
								}
							}
							cs = 0;
							goto _again;
						}
					}
					_match_cond:  {
						cs = (int)_sast_cond_targs[_cond];
						
						if ( _sast_cond_actions[_cond] == 0 )
						goto _again;
						
						_acts = ( _sast_actions + (_sast_cond_actions[_cond]));
						_nacts = (unsigned int)(*( _acts));
						_acts += 1;
						while ( _nacts > 0 )
						{
							switch ( (*( _acts)) )
							{
								case 0:  {
									{
										#line 57 "lexer.rl"
										AddNewline(p);}
									break; }
								case 3:  {
									{
										#line 1 "NONE"
										{te = p+1;}}
									break; }
								case 4:  {
									{
										#line 60 "lexer.rl"
										{te = p+1;{
												#line 60 "lexer.rl"
												
												Token(TokenKind::Comment);
												{cs = 6; goto _again;}}}}
									break; }
								case 5:  {
									{
										#line 65 "lexer.rl"
										{te = p+1;{
												#line 65 "lexer.rl"
												
												Token(TokenKind::Comment);
												{cs = 6; goto _again;}}}}
									break; }
								case 6:  {
									{
										#line 60 "lexer.rl"
										{te = p;p = p - 1;{
												#line 60 "lexer.rl"
												
												Token(TokenKind::Comment);
												{cs = 6; goto _again;}}}}
									break; }
								case 7:  {
									{
										#line 65 "lexer.rl"
										{te = p;p = p - 1;{
												#line 65 "lexer.rl"
												
												Token(TokenKind::Comment);
												{cs = 6; goto _again;}}}}
									break; }
								case 8:  {
									{
										#line 65 "lexer.rl"
										{p = ((te))-1;
											{
												#line 65 "lexer.rl"
												
												Token(TokenKind::Comment);
												{cs = 6; goto _again;}}}}
									break; }
								case 9:  {
									{
										#line 72 "lexer.rl"
										{te = p+1;{
												#line 72 "lexer.rl"
												
												Token(TokenKind::String, 1);
												{cs = 6; goto _again;}}}}
									break; }
								case 10:  {
									{
										#line 96 "lexer.rl"
										{act = 8;}}
									break; }
								case 11:  {
									{
										#line 119 "lexer.rl"
										{act = 13;}}
									break; }
								case 12:  {
									{
										#line 83 "lexer.rl"
										{te = p+1;{
												#line 83 "lexer.rl"
												
											}}}
									break; }
								case 13:  {
									{
										#line 86 "lexer.rl"
										{te = p+1;{
												#line 86 "lexer.rl"
												
												{p = p - 1; }
												{cs = 12; goto _again;}}}}
									break; }
								case 14:  {
									{
										#line 91 "lexer.rl"
										{te = p+1;{
												#line 91 "lexer.rl"
												
												{p = p - 1; }
												{cs = 15; goto _again;}}}}
									break; }
								case 15:  {
									{
										#line 101 "lexer.rl"
										{te = p+1;{
												#line 101 "lexer.rl"
												
												Token((( (*( p)))));
												++nesting;
											}}}
									break; }
								case 16:  {
									{
										#line 106 "lexer.rl"
										{te = p+1;{
												#line 106 "lexer.rl"
												
												Token((( (*( p)))));
												--nesting;
											}}}
									break; }
								case 17:  {
									{
										#line 115 "lexer.rl"
										{te = p+1;{
												#line 115 "lexer.rl"
												
												Token(TokenKind::Symbol);
											}}}
									break; }
								case 18:  {
									{
										#line 123 "lexer.rl"
										{te = p+1;{
												#line 123 "lexer.rl"
												
												Token((( (*( p)))));
											}}}
									break; }
								case 19:  {
									{
										#line 80 "lexer.rl"
										{te = p;p = p - 1;{
												#line 80 "lexer.rl"
												
											}}}
									break; }
								case 20:  {
									{
										#line 83 "lexer.rl"
										{te = p;p = p - 1;{
												#line 83 "lexer.rl"
												
											}}}
									break; }
								case 21:  {
									{
										#line 111 "lexer.rl"
										{te = p;p = p - 1;{
												#line 111 "lexer.rl"
												
												Token(TokenKind::Number);
											}}}
									break; }
								case 22:  {
									{
										#line 111 "lexer.rl"
										{p = ((te))-1;
											{
												#line 111 "lexer.rl"
												
												Token(TokenKind::Number);
											}}}
									break; }
								case 23:  {
									{
										#line 1 "NONE"
										{switch( act ) {
												case 8:  {
													p = ((te))-1;
													{
														#line 96 "lexer.rl"
														
														printf("TAB ERROR\n");
														exit(-1);
													} break; }
												case 13:  {
													p = ((te))-1;
													{
														#line 119 "lexer.rl"
														
														Token(TokenKind::Symbol);
													} break; }
											}}
									}
									break; }
							}
							_nacts -= 1;
							_acts += 1;
						}
						
						
					}
					_again:  {
						_acts = ( _sast_actions + (_sast_to_state_actions[cs]));
						_nacts = (unsigned int)(*( _acts));
						_acts += 1;
						while ( _nacts > 0 ) {
							switch ( (*( _acts)) ) {
								case 1:  {
									{
										#line 1 "NONE"
										{ts = 0;}}
									break; }
							}
							_nacts -= 1;
							_acts += 1;
						}
						
						if ( cs == 0 )
						goto _out;
						p += 1;
						if ( p != pe )
						goto _resume;
					}
					_test_eof:  { {}
						if ( p == eof )
						{
							if ( _sast_eof_trans_direct[cs] > 0 ) {
								_trans = (unsigned int)_sast_eof_trans_direct[cs] - 1;
								_cond = (unsigned int)_sast_trans_offsets[_trans];
								goto _match_cond;
							}
						}
						
					}
					_out:  { {}
					}
				}
			}
			
			#line 216 "lexer.rl"
			
			Token(0, 0, '}', eof - p, eof - p, 0);
		*tokens = (struct CToken *)malloc(this->tokens.size() * sizeof(struct CToken));
		copy(this->tokens.begin(), this->tokens.end(), *tokens);
		return this->tokens.size();
	}
	
};

extern "C" long scan(const char *source, struct CToken **tokens) {
	std::ios::sync_with_stdio(false);
	Lexer lexer(source);
	return lexer.Scan(tokens);
}

