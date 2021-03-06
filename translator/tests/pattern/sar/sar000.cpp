
/*******************************************************************************
 * Copyright 2020 FUJITSU LIMITED
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *******************************************************************************/
#include "test_generator2.h"

class TestPtnGenerator : public TestGenerator {
public:
  void setInitialRegValue() {
    /* Here modify arrays of inputGenReg, inputPredReg, inputZReg */
  }

  void setCheckRegFlagAll() {
    /* Here modify arrays of checkGenRegMode, checkPredRegMode, checkZRegMode */
  }

  void genJitTestCode() {
    /* Here write JIT code with x86_64 mnemonic function to be tested. */
    // mov(r8, uint64_t(0xaaaaaaaaaaaaaaaa));
    // mov(r9, uint32_t(0xaaaaaaaa));
    // mov(r10, uint16_t(0xaaaa));
    // mov(r11, uint8_t(0xaa));
    // mov(r11, ~uint64_t(0));

    mov(r12, int64_t(0xaaaaaaaaaaaaaaaa));
    // mov(r12, int64_t(0xaaaaaaaaaaaaaaaa));
    // mov(r13, int32_t(0xaaaaaaaa));
    mov(r14, int16_t(0xaaa0));
    mov(rax, 1);
    mov(rcx, 1);
    mov(rdx, 1);
    mov(rbx, 1);

    // mov(rax, int64_t(0x5555555555555555));
    // mov(rcx, int32_t(0x55555555));
    // mov(rdx, int16_t(0x5555));
    // mov(rbx, int8_t(0x55));

    sar(r12, 4);
    adc(rax, rcx);
    sar(r14, 4);
    adc(rdx, rbx);
  }
};

int main(int argc, char *argv[]) {
  /* Initializing arrays of inputData, inputGenReg, inputPredReg, inputZReg,
   * checkGenRegMode, checkPredRegMode,checkZRegMode */
  TestPtnGenerator gen;

  /* Set bool output_jit_on_, bool exec_jit_on_ = 0; */
  gen.parseArgs(argc, argv);

  /* Generate JIT code and get function pointer */
  void (*f)();
  if (gen.isOutputJitOn()) {
    f = (void (*)())gen.gen();
  }

  /* Dump generated JIT code to a binary file */
  gen.dumpJitCode();

  /* 1:Execute JIT code, 2:dump all register values, 3:dump register values to
   * be checked */
  if (gen.isExecJitOn()) {
    /* Before executing JIT code, dump inputData, inputGenReg, inputPredReg,
     * inputZReg. */
    gen.dumpInputReg();
    f();                 /* Execute JIT code */
    gen.dumpOutputReg(); /* Dump all register values */
    gen.dumpCheckReg();  /* Dump register values to be checked */
  }

  return 0;
}
