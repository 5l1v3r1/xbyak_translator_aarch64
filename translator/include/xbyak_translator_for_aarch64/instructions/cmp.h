void translateCMP(xed_decoded_inst_t *p) {
  // unsigned int i, noperands, dstIdx, srcIdx;
  const xed_inst_t *xi = xed_decoded_inst_inst(p);

  const xed_operand_t *op1 =
      xed_inst_operand(xi, 0); // dstのオペランドのポインタを取得
  const xed_operand_t *op2 =
      xed_inst_operand(xi, 1); // dstのオペランドのポインタを取得
  xed_operand_enum_t isDst =
      xed_operand_name(op1); // dstのオペランドの名前を取得
  xed_operand_enum_t isSrc =
      xed_operand_name(op2); // srcのオペランドの名前を取得

  xed_uint_t isDstSize = xed_decoded_inst_operand_length_bits(p, 0);
  xed_uint_t isSrcSize = xed_decoded_inst_operand_length_bits(p, 1);

  Xbyak_aarch64::XReg tmp1(25);
  Xbyak_aarch64::XReg tmp2(26);
  Xbyak_aarch64::XReg ans(27);

  unsigned int a64_dstIdx;
  unsigned int a64_srcIdx;

  if (false || (isDstSize == 64 && isSrcSize == 64 &&
                isDst == XED_OPERAND_REG0 && isSrc == XED_OPERAND_MEM0)) {
    ldr(tmp1, Xbyak_aarch64::ptr(X_TMP_ADDR));
  }
  if (false ||
      (isDstSize == 64 && isSrcSize == 32 && isDst == XED_OPERAND_MEM0 &&
       isSrc == XED_OPERAND_IMM0) ||
      (isDstSize == 64 && isSrcSize == 8 && isDst == XED_OPERAND_MEM0 &&
       isSrc == XED_OPERAND_IMM0) ||
      (isDstSize == 64 && isSrcSize == 64 && isDst == XED_OPERAND_MEM0 &&
       isSrc == XED_OPERAND_REG0)) {
    ldr(ans, Xbyak_aarch64::ptr(X_TMP_ADDR));
  }
  if (false || (isDstSize == 64 && isSrcSize == 64 &&
                isDst == XED_OPERAND_REG0 && isSrc == XED_OPERAND_MEM0)) {
    Xbyak_aarch64::CodeGeneratorAArch64::CMP__(Xbyak_aarch64::XReg(a64_srcIdx),
                                               tmp1);
  }
  if (false ||
      (isDstSize == 64 && isSrcSize == 64 && isDst == XED_OPERAND_REG0 &&
       isSrc == XED_OPERAND_REG1) ||
      (isDstSize == 64 && isSrcSize == 64 && isDst == XED_OPERAND_REG0 &&
       isSrc == XED_OPERAND_REG1)) {
    unsigned int a64_srcIdx1 = xed_get_register_index(p, 0);
    unsigned int a64_srcIdx2 = xed_get_register_index(p, 1);
    Xbyak_aarch64::CodeGeneratorAArch64::CMP__(
        Xbyak_aarch64::XReg(a64_srcIdx1), Xbyak_aarch64::XReg(a64_srcIdx2));
  }
  if (false || (isDstSize == 64 && isSrcSize == 64 &&
                isDst == XED_OPERAND_MEM0 && isSrc == XED_OPERAND_REG0)) {
    Xbyak_aarch64::CodeGeneratorAArch64::CMP__(ans,
                                               Xbyak_aarch64::XReg(a64_srcIdx));
  }
  if (false ||
      (isDstSize == 64 && isSrcSize == 32 && isDst == XED_OPERAND_REG0 &&
       isSrc == XED_OPERAND_IMM0) ||
      (isDstSize == 64 && isSrcSize == 32 && isDst == XED_OPERAND_REG0 &&
       isSrc == XED_OPERAND_IMM0) ||
      (isDstSize == 64 && isSrcSize == 8 && isDst == XED_OPERAND_REG0 &&
       isSrc == XED_OPERAND_IMM0)) {
    xed_uint_t ibits;
    ibits = xed_decoded_inst_get_immediate_width_bits(p);
    xed_int32_t x = xed_decoded_inst_get_signed_immediate(p);
    xed_uint64_t y = XED_STATIC_CAST(
        xed_uint64_t, xed_sign_extend_arbitrary_to_64((xed_uint64_t)x, ibits));
    cmp_imm(Xbyak_aarch64::XReg(a64_srcIdx), y, tmp1, tmp2);
  }
  if (false ||
      (isDstSize == 64 && isSrcSize == 32 && isDst == XED_OPERAND_MEM0 &&
       isSrc == XED_OPERAND_IMM0) ||
      (isDstSize == 64 && isSrcSize == 8 && isDst == XED_OPERAND_MEM0 &&
       isSrc == XED_OPERAND_IMM0)) {
    xed_uint_t ibits;
    ibits = xed_decoded_inst_get_immediate_width_bits(p);
    xed_int32_t x = xed_decoded_inst_get_signed_immediate(p);
    xed_uint64_t y = XED_STATIC_CAST(
        xed_uint64_t, xed_sign_extend_arbitrary_to_64((xed_uint64_t)x, ibits));
    cmp_imm(ans, y, tmp1, tmp2);
  }
  if (false ||
      (isDstSize == 64 && isSrcSize == 32 && isDst == XED_OPERAND_MEM0 &&
       isSrc == XED_OPERAND_IMM0) ||
      (isDstSize == 64 && isSrcSize == 8 && isDst == XED_OPERAND_MEM0 &&
       isSrc == XED_OPERAND_IMM0) ||
      (isDstSize == 64 && isSrcSize == 64 && isDst == XED_OPERAND_MEM0 &&
       isSrc == XED_OPERAND_REG0)) {
    str(ans, Xbyak_aarch64::ptr(X_TMP_ADDR));
  }
  if (false ||
      (isDstSize == 8 && isSrcSize == 8 && isDst == XED_OPERAND_REG0 &&
       isSrc == XED_OPERAND_IMM0) ||
      (isDstSize == 16 && isSrcSize == 16 && isDst == XED_OPERAND_REG0 &&
       isSrc == XED_OPERAND_IMM0) ||
      (isDstSize == 32 && isSrcSize == 32 && isDst == XED_OPERAND_REG0 &&
       isSrc == XED_OPERAND_IMM0) ||
      (isDstSize == 8 && isSrcSize == 8 && isDst == XED_OPERAND_REG0 &&
       isSrc == XED_OPERAND_IMM0) ||
      (isDstSize == 8 && isSrcSize == 8 && isDst == XED_OPERAND_MEM0 &&
       isSrc == XED_OPERAND_IMM0) ||
      (isDstSize == 8 && isSrcSize == 8 && isDst == XED_OPERAND_REG0 &&
       isSrc == XED_OPERAND_IMM0) ||
      (isDstSize == 8 && isSrcSize == 8 && isDst == XED_OPERAND_MEM0 &&
       isSrc == XED_OPERAND_IMM0) ||
      (isDstSize == 8 && isSrcSize == 8 && isDst == XED_OPERAND_REG0 &&
       isSrc == XED_OPERAND_IMM0) ||
      (isDstSize == 8 && isSrcSize == 8 && isDst == XED_OPERAND_MEM0 &&
       isSrc == XED_OPERAND_IMM0) ||
      (isDstSize == 32 && isSrcSize == 32 && isDst == XED_OPERAND_REG0 &&
       isSrc == XED_OPERAND_IMM0) ||
      (isDstSize == 32 && isSrcSize == 32 && isDst == XED_OPERAND_MEM0 &&
       isSrc == XED_OPERAND_IMM0) ||
      (isDstSize == 16 && isSrcSize == 8 && isDst == XED_OPERAND_REG0 &&
       isSrc == XED_OPERAND_IMM0) ||
      (isDstSize == 16 && isSrcSize == 8 && isDst == XED_OPERAND_MEM0 &&
       isSrc == XED_OPERAND_IMM0) ||
      (isDstSize == 32 && isSrcSize == 8 && isDst == XED_OPERAND_REG0 &&
       isSrc == XED_OPERAND_IMM0) ||
      (isDstSize == 32 && isSrcSize == 8 && isDst == XED_OPERAND_MEM0 &&
       isSrc == XED_OPERAND_IMM0) ||
      (isDstSize == 8 && isSrcSize == 8 && isDst == XED_OPERAND_REG0 &&
       isSrc == XED_OPERAND_REG1) ||
      (isDstSize == 8 && isSrcSize == 8 && isDst == XED_OPERAND_MEM0 &&
       isSrc == XED_OPERAND_REG0) ||
      (isDstSize == 16 && isSrcSize == 16 && isDst == XED_OPERAND_REG0 &&
       isSrc == XED_OPERAND_REG1) ||
      (isDstSize == 16 && isSrcSize == 16 && isDst == XED_OPERAND_MEM0 &&
       isSrc == XED_OPERAND_REG0) ||
      (isDstSize == 32 && isSrcSize == 32 && isDst == XED_OPERAND_REG0 &&
       isSrc == XED_OPERAND_REG1) ||
      (isDstSize == 32 && isSrcSize == 32 && isDst == XED_OPERAND_MEM0 &&
       isSrc == XED_OPERAND_REG0) ||
      (isDstSize == 8 && isSrcSize == 8 && isDst == XED_OPERAND_REG0 &&
       isSrc == XED_OPERAND_REG1) ||
      (isDstSize == 8 && isSrcSize == 8 && isDst == XED_OPERAND_REG0 &&
       isSrc == XED_OPERAND_MEM0) ||
      (isDstSize == 16 && isSrcSize == 16 && isDst == XED_OPERAND_REG0 &&
       isSrc == XED_OPERAND_REG1) ||
      (isDstSize == 16 && isSrcSize == 16 && isDst == XED_OPERAND_REG0 &&
       isSrc == XED_OPERAND_MEM0) ||
      (isDstSize == 32 && isSrcSize == 32 && isDst == XED_OPERAND_REG0 &&
       isSrc == XED_OPERAND_REG1) ||
      (isDstSize == 32 && isSrcSize == 32 && isDst == XED_OPERAND_REG0 &&
       isSrc == XED_OPERAND_MEM0)) {
    std::cerr << "Unimplemented" << std::endl;
    assert(NULL);
  }
}