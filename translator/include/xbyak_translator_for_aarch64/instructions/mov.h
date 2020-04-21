void translateMOV(xed_decoded_inst_t *p) {
  namespace xa = Xbyak_aarch64;
  struct xt_a64fx_operands_struct_t a64;
  xt_construct_a64fx_operands(p, &a64);

  /* 2020/04/20 21:51 */

  /* Col=M103*/
  if (false ||
      (a64.dstWidth == 8 && a64.dstType == A64_OP_MEM &&
       a64.srcType == A64_OP_REG) ||
      (a64.dstWidth == 16 && a64.dstType == A64_OP_REG &&
       a64.srcType == A64_OP_REG) ||
      (a64.dstWidth == 8 && a64.dstType == A64_OP_MEM &&
       a64.srcType == A64_OP_IMM) ||
      (a64.dstWidth == 16 && a64.dstType == A64_OP_MEM &&
       a64.srcType == A64_OP_IMM)) {
    XT_UNIMPLEMENTED;
  }
  /* Col=N103*/
  if (false || (a64.dstWidth == 64 && a64.dstType == A64_OP_REG &&
                a64.srcType == A64_OP_REG)) {
    CodeGeneratorAArch64::mov(Xbyak_aarch64::XReg(a64.dstIdx),
                              Xbyak_aarch64::XReg(a64.srcIdx));
  }
  /* Col=O103*/
  if (false || (a64.dstWidth == 32 && a64.dstType == A64_OP_REG &&
                a64.srcType == A64_OP_REG)) {
    CodeGeneratorAArch64::mov(Xbyak_aarch64::WReg(a64.dstIdx),
                              Xbyak_aarch64::WReg(a64.srcIdx));
  }

  /* Col=Q103*/
  if (false || (a64.dstWidth == 16 && a64.dstType == A64_OP_MEM &&
                a64.srcType == A64_OP_REG)) {
    CodeGeneratorAArch64::and_(X_TMP_1, Xbyak_aarch64::XReg(a64.srcIdx),
                               uint32_t(0xFFFF));
  }
  /* Col=R103*/
  if (false || (a64.dstWidth == 64 && a64.dstType == A64_OP_MEM &&
                a64.srcType == A64_OP_REG)) {
    CodeGeneratorAArch64::str(Xbyak_aarch64::XReg(a64.srcIdx),
                              Xbyak_aarch64::ptr(X_TMP_ADDR));
  }
  /* Col=S103*/
  if (false || (a64.dstWidth == 32 && a64.dstType == A64_OP_MEM &&
                a64.srcType == A64_OP_REG)) {
    CodeGeneratorAArch64::str(Xbyak_aarch64::WReg(a64.srcIdx),
                              Xbyak_aarch64::ptr(X_TMP_ADDR));
  }
  /* Col=T103*/
  if (false ||
      (a64.dstWidth == 8 && a64.dstType == A64_OP_REG &&
       a64.srcType == A64_OP_MEM) ||
      (a64.dstWidth == 16 && a64.dstType == A64_OP_REG &&
       a64.srcType == A64_OP_MEM)) {
    CodeGeneratorAArch64::ldr(X_TMP_1, Xbyak_aarch64::ptr(X_TMP_ADDR));
  }
  /* Col=U103*/
  if (false || (a64.dstWidth == 64 && a64.dstType == A64_OP_REG &&
                a64.srcType == A64_OP_MEM)) {
    CodeGeneratorAArch64::ldr(Xbyak_aarch64::XReg(a64.dstIdx),
                              Xbyak_aarch64::ptr(X_TMP_ADDR));
  }
  /* Col=V103*/
  if (false || (a64.dstWidth == 32 && a64.dstType == A64_OP_REG &&
                a64.srcType == A64_OP_MEM)) {
    CodeGeneratorAArch64::ldr(Xbyak_aarch64::WReg(a64.dstIdx),
                              Xbyak_aarch64::ptr(X_TMP_ADDR));
  }

  /* Col=AA103*/
  if (false ||
      (a64.dstWidth == 8 && a64.dstType == A64_OP_REG &&
       a64.srcType == A64_OP_IMM) ||
      (a64.dstWidth == 16 && a64.dstType == A64_OP_REG &&
       a64.srcType == A64_OP_IMM)) {
    if (a64.simm != 0) {
      CodeGeneratorAArch64::mov_imm(X_TMP_1, static_cast<int64_t>(a64.simm),
                                    X_TMP_0);
    } else {
      CodeGeneratorAArch64::mov_imm(X_TMP_1, static_cast<uint64_t>(a64.uimm),
                                    X_TMP_0);
    }
  }

  /* Col=AG103*/
  if (false ||
      (a64.dstWidth == 32 && a64.dstType == A64_OP_REG &&
       a64.srcType == A64_OP_IMM) ||
      (a64.dstWidth == 32 && a64.dstType == A64_OP_REG &&
       a64.srcType == A64_OP_IMM) ||
      (a64.dstWidth == 64 && a64.dstType == A64_OP_REG &&
       a64.srcType == A64_OP_IMM)) {
    if (a64.simm != 0) {
      CodeGeneratorAArch64::mov_imm(xa::XReg(a64.dstIdx),
                                    static_cast<int64_t>(a64.simm), X_TMP_0);
    } else {
      CodeGeneratorAArch64::mov_imm(xa::XReg(a64.dstIdx),
                                    static_cast<uint64_t>(a64.uimm), X_TMP_0);
    }
  }
  /* Col=AD103*/
  if (false || (a64.dstWidth == 64 && a64.dstType == A64_OP_REG &&
                a64.srcType == A64_OP_IMM)) {
    if (a64.simm != 0) {
      CodeGeneratorAArch64::mov_imm(xa::XReg(a64.dstIdx),
                                    static_cast<int64_t>(a64.simm), X_TMP_0);
    } else {
      xed_uint64_t mask = ~uint64_t(0xffffffff);
      unsigned bits = (mask & a64.uimm) ? 64 : 32;
      xed_int64_t tmp = xed_sign_extend_arbitrary_to_64(a64.uimm, bits);
      CodeGeneratorAArch64::mov_imm(xa::XReg(a64.dstIdx), tmp, X_TMP_0);
    }
  }
  /* Col=AE103*/
  if (false ||
      (a64.dstWidth == 16 && a64.dstType == A64_OP_REG &&
       a64.srcType == A64_OP_MEM) ||
      (a64.dstWidth == 16 && a64.dstType == A64_OP_REG &&
       a64.srcType == A64_OP_IMM)) {
    CodeGeneratorAArch64::and_(Xbyak_aarch64::XReg(a64.dstIdx),
                               Xbyak_aarch64::XReg(a64.dstIdx),
                               uint64_t(0xFFFFFFFFFFFF0000));
  }
  /* Col=AF103*/
  if (false ||
      (a64.dstWidth == 16 && a64.dstType == A64_OP_REG &&
       a64.srcType == A64_OP_MEM) ||
      (a64.dstWidth == 16 && a64.dstType == A64_OP_REG &&
       a64.srcType == A64_OP_IMM)) {
    CodeGeneratorAArch64::and_(X_TMP_1, X_TMP_1, uint32_t(0xFFFF));
  }

  /* Col=AH103*/
  if (false ||
      (a64.dstWidth == 8 && a64.dstType == A64_OP_REG &&
       a64.srcType == A64_OP_MEM) ||
      (a64.dstWidth == 8 && a64.dstType == A64_OP_REG &&
       a64.srcType == A64_OP_IMM)) {
    CodeGeneratorAArch64::and_(Xbyak_aarch64::XReg(a64.dstIdx),
                               Xbyak_aarch64::XReg(a64.dstIdx),
                               uint64_t(0xFFFFFFFFFFFFFF00));
  }
  /* Col=AI103*/
  if (false ||
      (a64.dstWidth == 8 && a64.dstType == A64_OP_REG &&
       a64.srcType == A64_OP_MEM) ||
      (a64.dstWidth == 8 && a64.dstType == A64_OP_REG &&
       a64.srcType == A64_OP_IMM)) {
    CodeGeneratorAArch64::and_(X_TMP_1, X_TMP_1, uint32_t(0xFF));
  }
  /* Col=AJ103*/
  if (false ||
      (a64.dstWidth == 8 && a64.dstType == A64_OP_REG &&
       a64.srcType == A64_OP_MEM) ||
      (a64.dstWidth == 16 && a64.dstType == A64_OP_REG &&
       a64.srcType == A64_OP_MEM) ||
      (a64.dstWidth == 8 && a64.dstType == A64_OP_REG &&
       a64.srcType == A64_OP_IMM) ||
      (a64.dstWidth == 16 && a64.dstType == A64_OP_REG &&
       a64.srcType == A64_OP_IMM)) {
    CodeGeneratorAArch64::orr(Xbyak_aarch64::XReg(a64.dstIdx),
                              Xbyak_aarch64::XReg(a64.dstIdx), X_TMP_1);
  }
  /* Col=AK103*/
  if (false || (a64.dstWidth == 64 && a64.dstType == A64_OP_MEM &&
                a64.srcType == A64_OP_IMM)) {
    if (a64.simm != 0) {
      CodeGeneratorAArch64::mov_imm(X_TMP_0, static_cast<int64_t>(a64.simm),
                                    X_TMP_1);
    } else {
      xed_uint64_t mask = ~uint64_t(0xffffffff);
      unsigned bits = (mask & a64.uimm) ? 64 : 32;
      xed_int64_t tmp = xed_sign_extend_arbitrary_to_64(a64.uimm, bits);
      CodeGeneratorAArch64::mov_imm(X_TMP_0, tmp, X_TMP_1);
    }
    CodeGeneratorAArch64::str(X_TMP_0, xa::ptr(X_TMP_ADDR));
  }

  /* Col=AN103*/
  if (false ||
      (a64.dstWidth == 8 && a64.dstType == A64_OP_MEM &&
       a64.srcType == A64_OP_IMM) ||
      (a64.dstWidth == 16 && a64.dstType == A64_OP_MEM &&
       a64.srcType == A64_OP_IMM) ||
      (a64.dstWidth == 32 && a64.dstType == A64_OP_MEM &&
       a64.srcType == A64_OP_IMM)) {
    if (a64.simm != 0) {
      CodeGeneratorAArch64::mov_imm(X_TMP_0, static_cast<int64_t>(a64.simm),
                                    X_TMP_1);
    } else {
      CodeGeneratorAArch64::mov_imm(X_TMP_0, static_cast<uint64_t>(a64.uimm),
                                    X_TMP_1);
    }
  }

  /* Col=AP103*/
  if (false || (a64.dstWidth == 16 && a64.dstType == A64_OP_MEM &&
                a64.srcType == A64_OP_IMM)) {
    CodeGeneratorAArch64::and_(X_TMP_0, X_TMP_0, uint32_t(0xFFFF));
  }
  /* Col=AQ103*/
  if (false || (a64.dstWidth == 8 && a64.dstType == A64_OP_MEM &&
                a64.srcType == A64_OP_IMM)) {
    CodeGeneratorAArch64::and_(X_TMP_0, X_TMP_0, uint32_t(0xFF));
  }

  /* Col=AS103*/
  if (false ||
      (a64.dstWidth == 8 && a64.dstType == A64_OP_MEM &&
       a64.srcType == A64_OP_IMM) ||
      (a64.dstWidth == 16 && a64.dstType == A64_OP_MEM &&
       a64.srcType == A64_OP_IMM) ||
      (a64.dstWidth == 32 && a64.dstType == A64_OP_MEM &&
       a64.srcType == A64_OP_IMM)) {
    CodeGeneratorAArch64::str(W_TMP_0, Xbyak_aarch64::ptr(X_TMP_ADDR));
  }
  /* Col=AT103*/
  if (false || (a64.dstWidth == 16 && a64.dstType == A64_OP_MEM &&
                a64.srcType == A64_OP_REG)) {
    CodeGeneratorAArch64::str(X_TMP_1, Xbyak_aarch64::ptr(X_TMP_ADDR));
  }
}
