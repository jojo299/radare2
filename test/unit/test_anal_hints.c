
#include <r_anal.h>

#include "minunit.h"

const RAnalHint empty_hint = {
	.addr = UT64_MAX,
	.ptr = 0,
	.val = UT64_MAX,
	.jump = UT64_MAX,
	.fail = UT64_MAX,
	.ret = UT64_MAX,
	.arch = 0,
	.opcode = NULL,
	.syntax = NULL,
	.esil = NULL,
	.offset = NULL,
	.type = 0,
	.size = 0,
	.bits = 0,
	.new_bits = 0,
	.immbase = 0,
	.high = 0,
	.nword = 0,
	.stackframe = UT64_MAX,
};

bool hint_equals(const RAnalHint *a, const RAnalHint *b) {
#define CHECK_EQ(member) mu_assert_eq (a->member, b->member, "hint member " #member)
	CHECK_EQ (ptr);
	CHECK_EQ (val);
	CHECK_EQ (jump);
	CHECK_EQ (fail);
	CHECK_EQ (ret);
	CHECK_EQ (type);
	CHECK_EQ (size);
	CHECK_EQ (bits);
	CHECK_EQ (new_bits);
	CHECK_EQ (immbase);
	CHECK_EQ (high);
	CHECK_EQ (nword);
	CHECK_EQ (stackframe);
#undef CHECK_EQ
#define CHECK_STREQ(member) mu_assert_nullable_streq (a->member, b->member, "hint member " #member)
	CHECK_STREQ (arch);
	CHECK_STREQ (opcode);
	CHECK_STREQ (syntax);
	CHECK_STREQ (esil);
	CHECK_STREQ (offset);
#undef CHECK_STREQ
	return true;
}

#define assert_hint_eq(actual, expected) do { if (!hint_equals (actual, expected)) { return false; } } while (0)

bool test_r_anal_addr_hints() {
	RAnal *anal = r_anal_new ();
	RAnalHint *hint = r_anal_hint_get (anal, 0x1337);
	assert_hint_eq (hint, &empty_hint);
	r_anal_hint_free (hint);

	RAnalHint cur = empty_hint;
#define CHECK \
	hint = r_anal_hint_get (anal, 0x1337); \
	assert_hint_eq (hint, &cur); \
	r_anal_hint_free (hint);
	hint = r_anal_hint_get (anal, 0x1338); \
	assert_hint_eq (hint, &empty_hint); \
	r_anal_hint_free (hint);
	hint = r_anal_hint_get (anal, 0x1336); \
	assert_hint_eq (hint, &empty_hint); \
	r_anal_hint_free (hint);

	// set --------

	r_anal_hint_set_syntax (anal, 0x1337, "mysyntax");
	cur.syntax = "mysyntax";
	CHECK

	r_anal_hint_set_type (anal, 0x1337, R_ANAL_OP_TYPE_RET);
	cur.type = R_ANAL_OP_TYPE_RET;
	CHECK

	r_anal_hint_set_jump (anal, 0x1337, 0xdeadbeef);
	cur.jump = 0xdeadbeef;
	CHECK

	r_anal_hint_set_fail (anal, 0x1337, 0xc0ffee);
	cur.fail = 0xc0ffee;
	CHECK

	r_anal_hint_set_nword (anal, 0x1337, 42);
	cur.nword = 42;
	CHECK

	r_anal_hint_set_offset (anal, 0x1337, "mytypeoff");
	cur.offset = "mytypeoff";
	CHECK

	r_anal_hint_set_immbase (anal, 0x1337, 7);
	cur.immbase = 7;
	CHECK

	r_anal_hint_set_size (anal, 0x1337, 0x123);
	cur.size = 0x123;
	CHECK

	r_anal_hint_set_opcode (anal, 0x1337, "myopcode");
	cur.opcode = "myopcode";
	CHECK

	r_anal_hint_set_esil (anal, 0x1337, "/,-rf,rm");
	cur.esil = "/,-rf,rm";
	CHECK

	r_anal_hint_set_pointer (anal, 0x1337, 0x4242);
	cur.ptr = 0x4242;
	CHECK

	r_anal_hint_set_ret (anal, 0x1337, 0xf00d);
	cur.ret = 0xf00d;
	CHECK

	r_anal_hint_set_high (anal, 0x1337);
	cur.high = true;
	CHECK

	r_anal_hint_set_stackframe (anal, 0x1337, 0x4321);
	cur.stackframe = 0x4321;
	CHECK

	r_anal_hint_set_val (anal, 0x1337, 0x112358d);
	cur.val = 0x112358d;
	CHECK

	// unset --------

	r_anal_hint_unset_syntax (anal, 0x1337);
	cur.syntax = NULL;
	CHECK

	r_anal_hint_unset_type (anal, 0x1337);
	cur.type = 0;
	CHECK

	r_anal_hint_unset_jump (anal, 0x1337);
	cur.jump = UT64_MAX;
	CHECK

	r_anal_hint_unset_fail (anal, 0x1337);
	cur.fail = UT64_MAX;
	CHECK

	r_anal_hint_unset_nword (anal, 0x1337);
	cur.nword = 0;
	CHECK

	r_anal_hint_unset_offset (anal, 0x1337);
	cur.offset = NULL;
	CHECK

	r_anal_hint_unset_immbase (anal, 0x1337);
	cur.immbase = 0;
	CHECK

	r_anal_hint_unset_size (anal, 0x1337);
	cur.size = 0;
	CHECK

	r_anal_hint_unset_opcode (anal, 0x1337);
	cur.opcode = NULL;
	CHECK

	r_anal_hint_unset_esil (anal, 0x1337);
	cur.esil = NULL;
	CHECK

	r_anal_hint_unset_pointer (anal, 0x1337);
	cur.ptr = 0;
	CHECK

	r_anal_hint_unset_ret (anal, 0x1337);
	cur.ret = UT64_MAX;
	CHECK

	r_anal_hint_unset_high (anal, 0x1337);
	cur.high = false;
	CHECK

	r_anal_hint_unset_stackframe (anal, 0x1337);
	cur.stackframe = UT64_MAX;
	CHECK

	r_anal_hint_unset_val (anal, 0x1337);
	cur.val = UT64_MAX;
	CHECK

	r_anal_free (anal);
	mu_end;
#undef CHECK
}

bool all_tests() {
	mu_run_test(test_r_anal_addr_hints);
	return tests_passed != tests_run;
}

int main(int argc, char **argv) {
	return all_tests();
}