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
	Regex* reg;
	reg = new Regex("[a-zA-Z]");
	ASSERT_EQ(reg->match("a"),1);
	ASSERT_EQ(reg->match("b"),1);
	ASSERT_EQ(reg->match("c"),1);
	ASSERT_EQ(reg->match("d"),1);
	ASSERT_EQ(reg->match("e"),1);
	ASSERT_EQ(reg->match("f"),1);
	ASSERT_EQ(reg->match("g"),1);
	ASSERT_EQ(reg->match("h"),1);
	ASSERT_EQ(reg->match("i"),1);
	ASSERT_EQ(reg->match("j"),1);
	ASSERT_EQ(reg->match("k"),1);
	ASSERT_EQ(reg->match("l"),1);
	ASSERT_EQ(reg->match("m"),1);
	ASSERT_EQ(reg->match("n"),1);
	ASSERT_EQ(reg->match("o"),1);
	ASSERT_EQ(reg->match("p"),1);
	ASSERT_EQ(reg->match("q"),1);
	ASSERT_EQ(reg->match("r"),1);
	ASSERT_EQ(reg->match("s"),1);
	ASSERT_EQ(reg->match("t"),1);
	ASSERT_EQ(reg->match("u"),1);
	ASSERT_EQ(reg->match("v"),1);
	ASSERT_EQ(reg->match("w"),1);
	ASSERT_EQ(reg->match("x"),1);
	ASSERT_EQ(reg->match("y"),1);
	ASSERT_EQ(reg->match("z"),1);
	ASSERT_EQ(reg->match("A"),1);
	ASSERT_EQ(reg->match("B"),1);
	ASSERT_EQ(reg->match("C"),1);
	ASSERT_EQ(reg->match("D"),1);
	ASSERT_EQ(reg->match("E"),1);
	ASSERT_EQ(reg->match("F"),1);
	ASSERT_EQ(reg->match("G"),1);
	ASSERT_EQ(reg->match("H"),1);
	ASSERT_EQ(reg->match("I"),1);
	ASSERT_EQ(reg->match("J"),1);
	ASSERT_EQ(reg->match("K"),1);
	ASSERT_EQ(reg->match("L"),1);
	ASSERT_EQ(reg->match("M"),1);
	ASSERT_EQ(reg->match("N"),1);
	ASSERT_EQ(reg->match("O"),1);
	ASSERT_EQ(reg->match("P"),1);
	ASSERT_EQ(reg->match("Q"),1);
	ASSERT_EQ(reg->match("R"),1);
	ASSERT_EQ(reg->match("S"),1);
	ASSERT_EQ(reg->match("T"),1);
	ASSERT_EQ(reg->match("U"),1);
	ASSERT_EQ(reg->match("V"),1);
	ASSERT_EQ(reg->match("W"),1);
	ASSERT_EQ(reg->match("X"),1);
	ASSERT_EQ(reg->match("Y"),1);
	ASSERT_EQ(reg->match("Z"),1);
	ASSERT_EQ(reg->match("ab"),0);
	ASSERT_EQ(reg->match("abc"),0);

	free(reg); reg = new Regex("[a-zA-Z0-9_]");
	ASSERT_EQ(reg->match("a"),1);
	ASSERT_EQ(reg->match("b"),1);
	ASSERT_EQ(reg->match("c"),1);
	ASSERT_EQ(reg->match("d"),1);
	ASSERT_EQ(reg->match("e"),1);
	ASSERT_EQ(reg->match("f"),1);
	ASSERT_EQ(reg->match("g"),1);
	ASSERT_EQ(reg->match("h"),1);
	ASSERT_EQ(reg->match("i"),1);
	ASSERT_EQ(reg->match("j"),1);
	ASSERT_EQ(reg->match("k"),1);
	ASSERT_EQ(reg->match("l"),1);
	ASSERT_EQ(reg->match("m"),1);
	ASSERT_EQ(reg->match("n"),1);
	ASSERT_EQ(reg->match("o"),1);
	ASSERT_EQ(reg->match("p"),1);
	ASSERT_EQ(reg->match("q"),1);
	ASSERT_EQ(reg->match("r"),1);
	ASSERT_EQ(reg->match("s"),1);
	ASSERT_EQ(reg->match("t"),1);
	ASSERT_EQ(reg->match("u"),1);
	ASSERT_EQ(reg->match("v"),1);
	ASSERT_EQ(reg->match("w"),1);
	ASSERT_EQ(reg->match("x"),1);
	ASSERT_EQ(reg->match("y"),1);
	ASSERT_EQ(reg->match("z"),1);
	ASSERT_EQ(reg->match("A"),1);
	ASSERT_EQ(reg->match("B"),1);
	ASSERT_EQ(reg->match("C"),1);
	ASSERT_EQ(reg->match("D"),1);
	ASSERT_EQ(reg->match("E"),1);
	ASSERT_EQ(reg->match("F"),1);
	ASSERT_EQ(reg->match("G"),1);
	ASSERT_EQ(reg->match("H"),1);
	ASSERT_EQ(reg->match("I"),1);
	ASSERT_EQ(reg->match("J"),1);
	ASSERT_EQ(reg->match("K"),1);
	ASSERT_EQ(reg->match("L"),1);
	ASSERT_EQ(reg->match("M"),1);
	ASSERT_EQ(reg->match("N"),1);
	ASSERT_EQ(reg->match("O"),1);
	ASSERT_EQ(reg->match("P"),1);
	ASSERT_EQ(reg->match("Q"),1);
	ASSERT_EQ(reg->match("R"),1);
	ASSERT_EQ(reg->match("S"),1);
	ASSERT_EQ(reg->match("T"),1);
	ASSERT_EQ(reg->match("U"),1);
	ASSERT_EQ(reg->match("V"),1);
	ASSERT_EQ(reg->match("W"),1);
	ASSERT_EQ(reg->match("X"),1);
	ASSERT_EQ(reg->match("Y"),1);
	ASSERT_EQ(reg->match("Z"),1);
	ASSERT_EQ(reg->match("0"),1);
	ASSERT_EQ(reg->match("1"),1);
	ASSERT_EQ(reg->match("2"),1);
	ASSERT_EQ(reg->match("3"),1);
	ASSERT_EQ(reg->match("4"),1);
	ASSERT_EQ(reg->match("5"),1);
	ASSERT_EQ(reg->match("6"),1);
	ASSERT_EQ(reg->match("7"),1);
	ASSERT_EQ(reg->match("8"),1);
	ASSERT_EQ(reg->match("9"),1);
	ASSERT_EQ(reg->match("_"),1);
	ASSERT_EQ(reg->match("ab"),0);
	ASSERT_EQ(reg->match("abc"),0);
}

TEST(RegexMatchTest, Multiplier) {
	Regex* reg;
	reg = new Regex("e{3}");
	ASSERT_EQ(reg->match("eee"),1);
	ASSERT_EQ(reg->match("teee"),0);
	ASSERT_EQ(reg->match("eeet"),0);

	free(reg);reg = new Regex("e{1,}");
	ASSERT_EQ(reg->match("e"),1);
	ASSERT_EQ(reg->match("ee"),1);
	ASSERT_EQ(reg->match("eee"),1);
	ASSERT_EQ(reg->match("ete"),0);
	ASSERT_EQ(reg->match(""),0);
	ASSERT_EQ(reg->match("te"),0);

	free(reg);reg = new Regex("et{1,2}");
	ASSERT_EQ(reg->match("et"),1);
	ASSERT_EQ(reg->match("ett"),1);
	ASSERT_EQ(reg->match("ettt"),0);
	ASSERT_EQ(reg->match("ete"),0);

	free(reg);reg = new Regex("(es){1,2}");
	ASSERT_EQ(reg->match("es"),1);
	ASSERT_EQ(reg->match("eses"),1);
	ASSERT_EQ(reg->match("eseses"),0);

	free(reg);reg = new Regex("(es*){1,2}");
	ASSERT_EQ(reg->match("e"),1);
	ASSERT_EQ(reg->match("ess"),1);
	ASSERT_EQ(reg->match("esss"),1);
	ASSERT_EQ(reg->match("ee"),1);
	ASSERT_EQ(reg->match("ees"),1);
	ASSERT_EQ(reg->match("eess"),1);
	ASSERT_EQ(reg->match("ese"),1);
	ASSERT_EQ(reg->match("esse"),1);
	ASSERT_EQ(reg->match("essse"),1);
	ASSERT_EQ(reg->match("eses"),1);
	ASSERT_EQ(reg->match("esess"),1);
	ASSERT_EQ(reg->match("esesss"),1);
	ASSERT_EQ(reg->match("esses"),1);
	ASSERT_EQ(reg->match("essess"),1);
	ASSERT_EQ(reg->match("essesss"),1);
	ASSERT_EQ(reg->match("essses"),1);
	ASSERT_EQ(reg->match("esssess"),1);
	ASSERT_EQ(reg->match("esssesss"),1);

	free(reg);reg = new Regex("((e)(s)){1,2}");
	ASSERT_EQ(reg->match("es"),1);
	ASSERT_EQ(reg->match("eses"),1);
	ASSERT_EQ(reg->match("eseses"),0);

	free(reg);reg = new Regex("((e))((s)){1,2}");
	ASSERT_EQ(reg->match("es"),1);
	ASSERT_EQ(reg->match("ess"),1);
	ASSERT_EQ(reg->match("esses"),0);
}

TEST(RegexMatchTest, SetMultiplier) {
	Regex* reg;
	reg = new Regex("[abc]{3}");
	ASSERT_EQ(reg->match("aaa"),1);
	ASSERT_EQ(reg->match("aab"),1);
	ASSERT_EQ(reg->match("aac"),1);
	ASSERT_EQ(reg->match("aba"),1);
	ASSERT_EQ(reg->match("abb"),1);
	ASSERT_EQ(reg->match("abc"),1);
	ASSERT_EQ(reg->match("aca"),1);
	ASSERT_EQ(reg->match("acb"),1);
	ASSERT_EQ(reg->match("acc"),1);
	ASSERT_EQ(reg->match("baa"),1);
	ASSERT_EQ(reg->match("bab"),1);
	ASSERT_EQ(reg->match("bac"),1);
	ASSERT_EQ(reg->match("bba"),1);
	ASSERT_EQ(reg->match("bbb"),1);
	ASSERT_EQ(reg->match("bbc"),1);
	ASSERT_EQ(reg->match("bca"),1);
	ASSERT_EQ(reg->match("bcb"),1);
	ASSERT_EQ(reg->match("bcc"),1);
	ASSERT_EQ(reg->match("caa"),1);
	ASSERT_EQ(reg->match("cab"),1);
	ASSERT_EQ(reg->match("cac"),1);
	ASSERT_EQ(reg->match("cba"),1);
	ASSERT_EQ(reg->match("cbb"),1);
	ASSERT_EQ(reg->match("cbc"),1);
	ASSERT_EQ(reg->match("cca"),1);
	ASSERT_EQ(reg->match("ccb"),1);
	ASSERT_EQ(reg->match("ccb"),1);
	ASSERT_EQ(reg->match("ddd"),0);
}

TEST(RegexMatchTest, EscapeLiteralSimple) {
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
}

TEST(RegexMatchTest, EscapeLiteralEasy) {
	Regex* reg;
	reg = new Regex("\\{\\}");
	ASSERT_EQ(reg->match("{}"),1);
	free(reg); reg = new Regex("\\[\\]");
	ASSERT_EQ(reg->match("[]"),1);
	free(reg); reg = new Regex("\\(\\)");
	ASSERT_EQ(reg->match("()"),1);
	free(reg); reg = new Regex("(\\(\\))");
	ASSERT_EQ(reg->match("()"),1);
	free(reg); reg = new Regex("(\\(\\)");
	ASSERT_EQ(reg->match(""),1);
	free(reg); reg = new Regex("\\(\\))");
	ASSERT_EQ(reg->match(""),1);
}

TEST(RegexMatchTest, EscapeSet) {
	Regex* reg;
	reg = new Regex("\\d");
	ASSERT_EQ(reg->match("0"),1);
	ASSERT_EQ(reg->match("1"),1);
	ASSERT_EQ(reg->match("2"),1);
	ASSERT_EQ(reg->match("3"),1);
	ASSERT_EQ(reg->match("4"),1);
	ASSERT_EQ(reg->match("5"),1);
	ASSERT_EQ(reg->match("6"),1);
	ASSERT_EQ(reg->match("7"),1);
	ASSERT_EQ(reg->match("8"),1);
	ASSERT_EQ(reg->match("9"),1);

	free(reg); reg = new Regex("\\w");
	free(reg); reg = new Regex("[a-zA-Z0-9_]");
	ASSERT_EQ(reg->match("a"),1);
	ASSERT_EQ(reg->match("b"),1);
	ASSERT_EQ(reg->match("c"),1);
	ASSERT_EQ(reg->match("d"),1);
	ASSERT_EQ(reg->match("e"),1);
	ASSERT_EQ(reg->match("f"),1);
	ASSERT_EQ(reg->match("g"),1);
	ASSERT_EQ(reg->match("h"),1);
	ASSERT_EQ(reg->match("i"),1);
	ASSERT_EQ(reg->match("j"),1);
	ASSERT_EQ(reg->match("k"),1);
	ASSERT_EQ(reg->match("l"),1);
	ASSERT_EQ(reg->match("m"),1);
	ASSERT_EQ(reg->match("n"),1);
	ASSERT_EQ(reg->match("o"),1);
	ASSERT_EQ(reg->match("p"),1);
	ASSERT_EQ(reg->match("q"),1);
	ASSERT_EQ(reg->match("r"),1);
	ASSERT_EQ(reg->match("s"),1);
	ASSERT_EQ(reg->match("t"),1);
	ASSERT_EQ(reg->match("u"),1);
	ASSERT_EQ(reg->match("v"),1);
	ASSERT_EQ(reg->match("w"),1);
	ASSERT_EQ(reg->match("x"),1);
	ASSERT_EQ(reg->match("y"),1);
	ASSERT_EQ(reg->match("z"),1);
	ASSERT_EQ(reg->match("A"),1);
	ASSERT_EQ(reg->match("B"),1);
	ASSERT_EQ(reg->match("C"),1);
	ASSERT_EQ(reg->match("D"),1);
	ASSERT_EQ(reg->match("E"),1);
	ASSERT_EQ(reg->match("F"),1);
	ASSERT_EQ(reg->match("G"),1);
	ASSERT_EQ(reg->match("H"),1);
	ASSERT_EQ(reg->match("I"),1);
	ASSERT_EQ(reg->match("J"),1);
	ASSERT_EQ(reg->match("K"),1);
	ASSERT_EQ(reg->match("L"),1);
	ASSERT_EQ(reg->match("M"),1);
	ASSERT_EQ(reg->match("N"),1);
	ASSERT_EQ(reg->match("O"),1);
	ASSERT_EQ(reg->match("P"),1);
	ASSERT_EQ(reg->match("Q"),1);
	ASSERT_EQ(reg->match("R"),1);
	ASSERT_EQ(reg->match("S"),1);
	ASSERT_EQ(reg->match("T"),1);
	ASSERT_EQ(reg->match("U"),1);
	ASSERT_EQ(reg->match("V"),1);
	ASSERT_EQ(reg->match("W"),1);
	ASSERT_EQ(reg->match("X"),1);
	ASSERT_EQ(reg->match("Y"),1);
	ASSERT_EQ(reg->match("Z"),1);
	ASSERT_EQ(reg->match("0"),1);
	ASSERT_EQ(reg->match("1"),1);
	ASSERT_EQ(reg->match("2"),1);
	ASSERT_EQ(reg->match("3"),1);
	ASSERT_EQ(reg->match("4"),1);
	ASSERT_EQ(reg->match("5"),1);
	ASSERT_EQ(reg->match("6"),1);
	ASSERT_EQ(reg->match("7"),1);
	ASSERT_EQ(reg->match("8"),1);
	ASSERT_EQ(reg->match("9"),1);
	ASSERT_EQ(reg->match("_"),1);
	ASSERT_EQ(reg->match("ab"),0);
	ASSERT_EQ(reg->match("abc"),0);

	free(reg); reg = new Regex("\\s");
	ASSERT_EQ(reg->match("\n"),1);
	ASSERT_EQ(reg->match("\t"),1);
	ASSERT_EQ(reg->match("\r"),1);
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
