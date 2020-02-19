void translateVMOVLPS(xed_decoded_inst_t *p) {
  namespace xa = Xbyak_aarch64;
  struct xt_a64fx_operands_struct_t a64;
  xt_construct_a64fx_operands(p, &a64);

  /* 2020/02/19 13:02 */
  /* Col=U103*/
  if(false ||(a64.dstType==A64_OP_REG&&a64.srcType==A64_OP_REG&&a64.src2Type==A64_OP_MEM&&true)) {
    a64.vTmpIdx = xt_push_vreg(&a64);
  }
  /* Col=Y103*/
  if(false ||(a64.dstType==A64_OP_REG&&a64.srcType==A64_OP_REG&&a64.src2Type==A64_OP_MEM&&true)) {
    CodeGeneratorAArch64::mov(xa::VReg2D(a64.dstIdx)[1], xa::VReg2D(a64.srcIdx)[1]);
  }
  /* Col=AD103*/
  if(false ||(a64.dstType==A64_OP_REG&&a64.srcType==A64_OP_REG&&a64.src2Type==A64_OP_MEM&&true)) {
    CodeGeneratorAArch64::ldr(xa::QReg(a64.vTmpIdx), xa::ptr(X_TMP_ADDR));
  }
  /* Col=AH103*/
  if(false ||(a64.dstType==A64_OP_REG&&a64.srcType==A64_OP_REG&&a64.src2Type==A64_OP_MEM&&true)) {
    CodeGeneratorAArch64::mov(xa::VReg2D(a64.dstIdx)[0], xa::VReg2D(a64.vTmpIdx)[0]);
  }
  /* Col=AL103*/
  if(false ||(a64.dstType==A64_OP_REG&&a64.srcType==A64_OP_REG&&a64.src2Type==A64_OP_MEM&&true)) {
    xt_pop_vreg();
  }
  /* Col=AP103*/
  if(false ||(a64.dstType==A64_OP_MEM&&a64.srcType==A64_OP_REG&&true)) {
    CodeGeneratorAArch64::st1(xa::VReg2D(a64.srcIdx)[0], xa::ptr(X_TMP_ADDR));
  }
}
