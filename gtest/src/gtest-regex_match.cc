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

TEST(RegexMatchTest, Concat) {
	Regex r("te");
	ASSERT_EQ(r.match("te"),1);
	ASSERT_EQ(r.match("t"),0);
	ASSERT_EQ(r.match("e"),0);
}

TEST(RegexMatchTest, Or) {
	Regex r("te|st");
	ASSERT_EQ(r.match("te"),1);
	ASSERT_EQ(r.match("st"),1);
	ASSERT_EQ(r.match("test"),0);
	ASSERT_EQ(r.match("ts"),0);
	ASSERT_EQ(r.match("et"),0);
}

TEST(RegexMatchTest, Star) {
	Regex r("t*");
	ASSERT_EQ(r.match(""),1);
	ASSERT_EQ(r.match("t"),1);
	ASSERT_EQ(r.match("tt"),1);
	ASSERT_EQ(r.match("ttt"),1);
	ASSERT_EQ(r.match("tttt"),1);
	ASSERT_EQ(r.match("ttttt"),1);
	ASSERT_EQ(r.match("et"),0);
	ASSERT_EQ(r.match("ett"),0);
	ASSERT_EQ(r.match("etet"),0);
}

TEST(RegexMatchTest, Plus) {
	Regex r("t+");
	ASSERT_EQ(r.match("t"),1);
	ASSERT_EQ(r.match("tt"),1);
	ASSERT_EQ(r.match("ttt"),1);
	ASSERT_EQ(r.match("tttt"),1);
	ASSERT_EQ(r.match("ttttt"),1);
	ASSERT_EQ(r.match("et"),0);
	ASSERT_EQ(r.match("ett"),0);
	ASSERT_EQ(r.match("etet"),0);
}

TEST(RegexMatchTest, Question) {
	Regex r("t?");
	ASSERT_EQ(r.match(""),1);
	ASSERT_EQ(r.match("t"),1);
	ASSERT_EQ(r.match("tt"),0);
	ASSERT_EQ(r.match("et"),0);
	ASSERT_EQ(r.match("ett"),0);
	ASSERT_EQ(r.match("etet"),0);
}

TEST(RegexMatchTest, Parenthesis) {
	Regex r("(te)*");
	ASSERT_EQ(r.match(""),1);
	ASSERT_EQ(r.match("te"),1);
	ASSERT_EQ(r.match("tete"),1);
	ASSERT_EQ(r.match("tt"),0);
	ASSERT_EQ(r.match("ee"),0);
	ASSERT_EQ(r.match("teet"),0);
}

TEST(RegexMatchTest, Grouping) {
	Regex r("[abc]");
	ASSERT_EQ(r.match("a"),1);
	ASSERT_EQ(r.match("b"),1);
	ASSERT_EQ(r.match("c"),1);
	ASSERT_EQ(r.match("ab"),0);
	ASSERT_EQ(r.match("bc"),0);
	ASSERT_EQ(r.match("ab"),0);
	ASSERT_EQ(r.match(""),0);
}

TEST(RegexMatchTest, Range) {
	Regex r("[a-z][a-c]*");
	ASSERT_EQ(r.match("a"),1);
	ASSERT_EQ(r.match("b"),1);
	ASSERT_EQ(r.match("c"),1);
	ASSERT_EQ(r.match("d"),1);
	ASSERT_EQ(r.match("e"),1);
	ASSERT_EQ(r.match("f"),1);
	ASSERT_EQ(r.match("g"),1);
	ASSERT_EQ(r.match("h"),1);
	ASSERT_EQ(r.match("i"),1);
	ASSERT_EQ(r.match("j"),1);
	ASSERT_EQ(r.match("k"),1);
	ASSERT_EQ(r.match("l"),1);
	ASSERT_EQ(r.match("m"),1);
	ASSERT_EQ(r.match("n"),1);
	ASSERT_EQ(r.match("o"),1);
	ASSERT_EQ(r.match("p"),1);
	ASSERT_EQ(r.match("q"),1);
	ASSERT_EQ(r.match("r"),1);
	ASSERT_EQ(r.match("s"),1);
	ASSERT_EQ(r.match("t"),1);
	ASSERT_EQ(r.match("u"),1);
	ASSERT_EQ(r.match("v"),1);
	ASSERT_EQ(r.match("w"),1);
	ASSERT_EQ(r.match("x"),1);
	ASSERT_EQ(r.match("y"),1);
	ASSERT_EQ(r.match("z"),1);
	ASSERT_EQ(r.match("hb"),1);
	ASSERT_EQ(r.match("abc"),1);
}

TEST(RegexMatchTest, RangeJoin) {
	Regex r("[a-zA-Z]");
	ASSERT_EQ(r.match("a"),1);
	ASSERT_EQ(r.match("b"),1);
	ASSERT_EQ(r.match("c"),1);
	ASSERT_EQ(r.match("d"),1);
	ASSERT_EQ(r.match("e"),1);
	ASSERT_EQ(r.match("f"),1);
	ASSERT_EQ(r.match("g"),1);
	ASSERT_EQ(r.match("h"),1);
	ASSERT_EQ(r.match("i"),1);
	ASSERT_EQ(r.match("j"),1);
	ASSERT_EQ(r.match("k"),1);
	ASSERT_EQ(r.match("l"),1);
	ASSERT_EQ(r.match("m"),1);
	ASSERT_EQ(r.match("n"),1);
	ASSERT_EQ(r.match("o"),1);
	ASSERT_EQ(r.match("p"),1);
	ASSERT_EQ(r.match("q"),1);
	ASSERT_EQ(r.match("r"),1);
	ASSERT_EQ(r.match("s"),1);
	ASSERT_EQ(r.match("t"),1);
	ASSERT_EQ(r.match("u"),1);
	ASSERT_EQ(r.match("v"),1);
	ASSERT_EQ(r.match("w"),1);
	ASSERT_EQ(r.match("x"),1);
	ASSERT_EQ(r.match("y"),1);
	ASSERT_EQ(r.match("z"),1);
	ASSERT_EQ(r.match("A"),1);
	ASSERT_EQ(r.match("B"),1);
	ASSERT_EQ(r.match("C"),1);
	ASSERT_EQ(r.match("D"),1);
	ASSERT_EQ(r.match("E"),1);
	ASSERT_EQ(r.match("F"),1);
	ASSERT_EQ(r.match("G"),1);
	ASSERT_EQ(r.match("H"),1);
	ASSERT_EQ(r.match("I"),1);
	ASSERT_EQ(r.match("J"),1);
	ASSERT_EQ(r.match("K"),1);
	ASSERT_EQ(r.match("L"),1);
	ASSERT_EQ(r.match("M"),1);
	ASSERT_EQ(r.match("N"),1);
	ASSERT_EQ(r.match("O"),1);
	ASSERT_EQ(r.match("P"),1);
	ASSERT_EQ(r.match("Q"),1);
	ASSERT_EQ(r.match("R"),1);
	ASSERT_EQ(r.match("S"),1);
	ASSERT_EQ(r.match("T"),1);
	ASSERT_EQ(r.match("U"),1);
	ASSERT_EQ(r.match("V"),1);
	ASSERT_EQ(r.match("W"),1);
	ASSERT_EQ(r.match("X"),1);
	ASSERT_EQ(r.match("Y"),1);
	ASSERT_EQ(r.match("Z"),1);
	ASSERT_EQ(r.match("ab"),0);
	ASSERT_EQ(r.match("abc"),0);
}

TEST(RegexMatchTest, Multiplier) {
	Regex t("e{3}");
	ASSERT_EQ(t.match("eee"),1);
	ASSERT_EQ(t.match("teee"),0);
	ASSERT_EQ(t.match("eeet"),0);
	Regex s("e{1,}");
	ASSERT_EQ(s.match("e"),1);
	ASSERT_EQ(s.match("ee"),1);
	ASSERT_EQ(s.match("eee"),1);
	ASSERT_EQ(s.match("ete"),0);
	ASSERT_EQ(s.match(""),0);
	ASSERT_EQ(s.match("te"),0);
	Regex r("et{1,2}");
	ASSERT_EQ(r.match("et"),1);
	ASSERT_EQ(r.match("ett"),1);
	ASSERT_EQ(r.match("ettt"),0);
	ASSERT_EQ(r.match("ete"),0);
}

TEST(RegexMatchTest, EscapeLiteral) {
	Regex* reg;
	reg = new Regex("\\}");
	ASSERT_EQ(reg->match("}"),1);
	free(reg); reg = new Regex("\\{");
	ASSERT_EQ(reg->match("{"),1);
	free(reg); reg = new Regex("\\[");
	ASSERT_EQ(reg->match("["),1);
	free(reg); reg = new Regex("\\]");
	ASSERT_EQ(reg->match("]"),1);
	free(reg); reg = new Regex("\\(");
	ASSERT_EQ(reg->match("("),1);
	free(reg); reg = new Regex("\\)");
	ASSERT_EQ(reg->match(")"),1);
	free(reg); reg = new Regex("\\.");
	ASSERT_EQ(reg->match("."),1);
	free(reg); reg = new Regex("\\*");
	ASSERT_EQ(reg->match("*"),1);
	free(reg); reg = new Regex("\\+");
	ASSERT_EQ(reg->match("+"),1);
	free(reg); reg = new Regex("\\?");
	ASSERT_EQ(reg->match("?"),1);
	free(reg); reg = new Regex("\\|");
	ASSERT_EQ(reg->match("|"),1);
	free(reg); reg = new Regex("\\}*\\{");
	ASSERT_EQ(reg->match("{"),1);
	ASSERT_EQ(reg->match("}{"),1);
	ASSERT_EQ(reg->match("}}{"),1);
	free(reg); reg = new Regex("\\][abc]\\[");
	ASSERT_EQ(reg->match("]a["),1);
	ASSERT_EQ(reg->match("]b["),1);
	ASSERT_EQ(reg->match("]c["),1);
	free(reg); reg = new Regex("\\}{2,}\\{");
	ASSERT_EQ(reg->match("}}{"),1);
	ASSERT_EQ(reg->match("}}}{"),1);
	ASSERT_EQ(reg->match("}}}}{"),1);
}


TEST(RegexMatchTest, CharSetAlpha) {
	Regex r("[:alpha:]");
	ASSERT_EQ(r.match("a"),1);
	ASSERT_EQ(r.match("b"),1);
	ASSERT_EQ(r.match("c"),1);
	ASSERT_EQ(r.match("d"),1);
	ASSERT_EQ(r.match("e"),1);
	ASSERT_EQ(r.match("f"),1);
	ASSERT_EQ(r.match("g"),1);
	ASSERT_EQ(r.match("h"),1);
	ASSERT_EQ(r.match("i"),1);
	ASSERT_EQ(r.match("j"),1);
	ASSERT_EQ(r.match("k"),1);
	ASSERT_EQ(r.match("l"),1);
	ASSERT_EQ(r.match("m"),1);
	ASSERT_EQ(r.match("n"),1);
	ASSERT_EQ(r.match("o"),1);
	ASSERT_EQ(r.match("p"),1);
	ASSERT_EQ(r.match("q"),1);
	ASSERT_EQ(r.match("r"),1);
	ASSERT_EQ(r.match("s"),1);
	ASSERT_EQ(r.match("t"),1);
	ASSERT_EQ(r.match("u"),1);
	ASSERT_EQ(r.match("v"),1);
	ASSERT_EQ(r.match("w"),1);
	ASSERT_EQ(r.match("x"),1);
	ASSERT_EQ(r.match("y"),1);
	ASSERT_EQ(r.match("z"),1);
	ASSERT_EQ(r.match("A"),1);
	ASSERT_EQ(r.match("B"),1);
	ASSERT_EQ(r.match("C"),1);
	ASSERT_EQ(r.match("D"),1);
	ASSERT_EQ(r.match("E"),1);
	ASSERT_EQ(r.match("F"),1);
	ASSERT_EQ(r.match("G"),1);
	ASSERT_EQ(r.match("H"),1);
	ASSERT_EQ(r.match("I"),1);
	ASSERT_EQ(r.match("J"),1);
	ASSERT_EQ(r.match("K"),1);
	ASSERT_EQ(r.match("L"),1);
	ASSERT_EQ(r.match("M"),1);
	ASSERT_EQ(r.match("N"),1);
	ASSERT_EQ(r.match("O"),1);
	ASSERT_EQ(r.match("P"),1);
	ASSERT_EQ(r.match("Q"),1);
	ASSERT_EQ(r.match("R"),1);
	ASSERT_EQ(r.match("S"),1);
	ASSERT_EQ(r.match("T"),1);
	ASSERT_EQ(r.match("U"),1);
	ASSERT_EQ(r.match("V"),1);
	ASSERT_EQ(r.match("W"),1);
	ASSERT_EQ(r.match("X"),1);
	ASSERT_EQ(r.match("Y"),1);
	ASSERT_EQ(r.match("Z"),1);
	ASSERT_EQ(r.match("ab"),0);
	ASSERT_EQ(r.match("abc"),0);
}
/*
TEST(RegexMatchTest, DotMatching) {
	Regex r(".");
	ASSERT_EQ(r.match(" "),1);
	ASSERT_EQ(r.match("0"),1);
	ASSERT_EQ(r.match("1"),1);
	ASSERT_EQ(r.match("2"),1);
	ASSERT_EQ(r.match("3"),1);
	ASSERT_EQ(r.match("4"),1);
	ASSERT_EQ(r.match("5"),1);
	ASSERT_EQ(r.match("6"),1);
	ASSERT_EQ(r.match("7"),1);
	ASSERT_EQ(r.match("8"),1);
	ASSERT_EQ(r.match("9"),1);
	ASSERT_EQ(r.match("a"),1);
	ASSERT_EQ(r.match("b"),1);
	ASSERT_EQ(r.match("c"),1);
	ASSERT_EQ(r.match("d"),1);
	ASSERT_EQ(r.match("e"),1);
	ASSERT_EQ(r.match("f"),1);
	ASSERT_EQ(r.match("g"),1);
	ASSERT_EQ(r.match("h"),1);
	ASSERT_EQ(r.match("i"),1);
	ASSERT_EQ(r.match("j"),1);
	ASSERT_EQ(r.match("k"),1);
	ASSERT_EQ(r.match("l"),1);
	ASSERT_EQ(r.match("m"),1);
	ASSERT_EQ(r.match("n"),1);
	ASSERT_EQ(r.match("o"),1);
	ASSERT_EQ(r.match("p"),1);
	ASSERT_EQ(r.match("q"),1);
	ASSERT_EQ(r.match("r"),1);
	ASSERT_EQ(r.match("s"),1);
	ASSERT_EQ(r.match("t"),1);
	ASSERT_EQ(r.match("u"),1);
	ASSERT_EQ(r.match("v"),1);
	ASSERT_EQ(r.match("w"),1);
	ASSERT_EQ(r.match("x"),1);
	ASSERT_EQ(r.match("y"),1);
	ASSERT_EQ(r.match("z"),1);
	ASSERT_EQ(r.match("A"),1);
	ASSERT_EQ(r.match("B"),1);
	ASSERT_EQ(r.match("C"),1);
	ASSERT_EQ(r.match("D"),1);
	ASSERT_EQ(r.match("E"),1);
	ASSERT_EQ(r.match("F"),1);
	ASSERT_EQ(r.match("G"),1);
	ASSERT_EQ(r.match("H"),1);
	ASSERT_EQ(r.match("I"),1);
	ASSERT_EQ(r.match("J"),1);
	ASSERT_EQ(r.match("K"),1);
	ASSERT_EQ(r.match("L"),1);
	ASSERT_EQ(r.match("M"),1);
	ASSERT_EQ(r.match("N"),1);
	ASSERT_EQ(r.match("O"),1);
	ASSERT_EQ(r.match("P"),1);
	ASSERT_EQ(r.match("Q"),1);
	ASSERT_EQ(r.match("R"),1);
	ASSERT_EQ(r.match("S"),1);
	ASSERT_EQ(r.match("T"),1);
	ASSERT_EQ(r.match("U"),1);
	ASSERT_EQ(r.match("V"),1);
	ASSERT_EQ(r.match("W"),1);
	ASSERT_EQ(r.match("X"),1);
	ASSERT_EQ(r.match("Y"),1);
	ASSERT_EQ(r.match("Z"),1);
	ASSERT_EQ(r.match("ab"),0);
	ASSERT_EQ(r.match("abc"),0);
}
*/

TEST(RegexMatchTest, NegationGrouping) {
	Regex r("[^abc]");
	ASSERT_EQ(r.match(" "),1);
	ASSERT_EQ(r.match("0"),1);
	ASSERT_EQ(r.match("1"),1);
	ASSERT_EQ(r.match("2"),1);
	ASSERT_EQ(r.match("3"),1);
	ASSERT_EQ(r.match("4"),1);
	ASSERT_EQ(r.match("5"),1);
	ASSERT_EQ(r.match("6"),1);
	ASSERT_EQ(r.match("7"),1);
	ASSERT_EQ(r.match("8"),1);
	ASSERT_EQ(r.match("9"),1);
	ASSERT_EQ(r.match("d"),1);
	ASSERT_EQ(r.match("e"),1);
	ASSERT_EQ(r.match("f"),1);
	ASSERT_EQ(r.match("g"),1);
	ASSERT_EQ(r.match("h"),1);
	ASSERT_EQ(r.match("i"),1);
	ASSERT_EQ(r.match("j"),1);
	ASSERT_EQ(r.match("k"),1);
	ASSERT_EQ(r.match("l"),1);
	ASSERT_EQ(r.match("m"),1);
	ASSERT_EQ(r.match("n"),1);
	ASSERT_EQ(r.match("o"),1);
	ASSERT_EQ(r.match("p"),1);
	ASSERT_EQ(r.match("q"),1);
	ASSERT_EQ(r.match("r"),1);
	ASSERT_EQ(r.match("s"),1);
	ASSERT_EQ(r.match("t"),1);
	ASSERT_EQ(r.match("u"),1);
	ASSERT_EQ(r.match("v"),1);
	ASSERT_EQ(r.match("w"),1);
	ASSERT_EQ(r.match("x"),1);
	ASSERT_EQ(r.match("y"),1);
	ASSERT_EQ(r.match("z"),1);
	ASSERT_EQ(r.match("A"),1);
	ASSERT_EQ(r.match("B"),1);
	ASSERT_EQ(r.match("C"),1);
	ASSERT_EQ(r.match("D"),1);
	ASSERT_EQ(r.match("E"),1);
	ASSERT_EQ(r.match("F"),1);
	ASSERT_EQ(r.match("G"),1);
	ASSERT_EQ(r.match("H"),1);
	ASSERT_EQ(r.match("I"),1);
	ASSERT_EQ(r.match("J"),1);
	ASSERT_EQ(r.match("K"),1);
	ASSERT_EQ(r.match("L"),1);
	ASSERT_EQ(r.match("M"),1);
	ASSERT_EQ(r.match("N"),1);
	ASSERT_EQ(r.match("O"),1);
	ASSERT_EQ(r.match("P"),1);
	ASSERT_EQ(r.match("Q"),1);
	ASSERT_EQ(r.match("R"),1);
	ASSERT_EQ(r.match("S"),1);
	ASSERT_EQ(r.match("T"),1);
	ASSERT_EQ(r.match("U"),1);
	ASSERT_EQ(r.match("V"),1);
	ASSERT_EQ(r.match("W"),1);
	ASSERT_EQ(r.match("X"),1);
	ASSERT_EQ(r.match("Y"),1);
	ASSERT_EQ(r.match("Z"),1);
	ASSERT_EQ(r.match("ab"),0);
	ASSERT_EQ(r.match("abc"),0);
}
