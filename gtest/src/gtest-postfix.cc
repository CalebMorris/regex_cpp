// Copyright 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// A sample program demonstrating using Google C++ testing framework.
//
// Author: wan@google.com (Zhanyong Wan)

#include "gtest/gtest.h"
#include "../../regex.hpp"

TEST(RegexToPostfixTest, Concat) {
	Regex r;
	ASSERT_EQ(r.regex_to_postfix("t"),"t");
	ASSERT_EQ(r.regex_to_postfix("te"),"te.");
}

TEST(RegexToPostfixTest, Or) {
	Regex r;
	ASSERT_EQ(r.regex_to_postfix("|te"),"");
	ASSERT_EQ(r.regex_to_postfix("t|"),"");
	ASSERT_EQ(r.regex_to_postfix("t|e"),"te|");
	ASSERT_EQ(r.regex_to_postfix("tes|e"),"te.s.e|");
	ASSERT_EQ(r.regex_to_postfix("t|est"),"tes.t.|");
	ASSERT_EQ(r.regex_to_postfix("test|er"),"te.s.t.er.|");
	ASSERT_EQ(r.regex_to_postfix("te|st|er"),"te.st.er.||");
}

TEST(RegexToPostfixTest, Star) {
	Regex r;
	ASSERT_EQ(r.regex_to_postfix("*t"),"");
	ASSERT_EQ(r.regex_to_postfix("t*"),"t*");
	ASSERT_EQ(r.regex_to_postfix("t*e"),"t*e.");
	ASSERT_EQ(r.regex_to_postfix("t*es"),"t*e.s.");
	ASSERT_EQ(r.regex_to_postfix("te*s"),"te*.s.");
}

TEST(RegexToPostfixTest, Plus) {
	Regex r;
	ASSERT_EQ(r.regex_to_postfix("+t"),"");
	ASSERT_EQ(r.regex_to_postfix("t+"),"t+");
	ASSERT_EQ(r.regex_to_postfix("t+e"),"t+e.");
	ASSERT_EQ(r.regex_to_postfix("t+es"),"t+e.s.");
	ASSERT_EQ(r.regex_to_postfix("te+s"),"te+.s.");
}

TEST(RegexToPostfixTest, QuestionMark) {
	Regex r;
	ASSERT_EQ(r.regex_to_postfix("?t"),"");
	ASSERT_EQ(r.regex_to_postfix("t?"),"t?");
	ASSERT_EQ(r.regex_to_postfix("t?e"),"t?e.");
	ASSERT_EQ(r.regex_to_postfix("t?es"),"t?e.s.");
	ASSERT_EQ(r.regex_to_postfix("te?s"),"te?.s.");
}

TEST(RegexToPostfixTest, Parenthesis) {
	Regex r;
	ASSERT_EQ(r.regex_to_postfix("("),"");
	ASSERT_EQ(r.regex_to_postfix(")"),"");
	ASSERT_EQ(r.regex_to_postfix("t()t"),"");
	ASSERT_EQ(r.regex_to_postfix("t)t(t"),"");
	ASSERT_EQ(r.regex_to_postfix("(t)"),"t");
	ASSERT_EQ(r.regex_to_postfix("(t*)"),"t*");
	ASSERT_EQ(r.regex_to_postfix("(t)*"),"t*");
	ASSERT_EQ(r.regex_to_postfix("(t*)*"),"t**");
	ASSERT_EQ(r.regex_to_postfix("(te)*"),"te.*");
	ASSERT_EQ(r.regex_to_postfix("ab(te)st"),"ab.te..s.t.");
	ASSERT_EQ(r.regex_to_postfix("(a|b)s"),"ab|s.");
}