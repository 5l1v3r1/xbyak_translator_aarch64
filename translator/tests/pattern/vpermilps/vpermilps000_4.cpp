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
    setInputZregAllRandomHex();
  }

  void setCheckRegFlagAll() {
    /* Here modify arrays of checkGenRegMode, checkPredRegMode, checkZRegMode */
  }

  void genJitTestCode() {
    /* Here write JIT code with x86_64 mnemonic function to be tested. */
    /* RAX, RCX, RDX, RBX, RSP, RBP, RSI, RDI,
       R8,  R9,  R10, R11, R12, R13, R14, R15 */

    /* VEX range */
    vpermilps(ymm0, ymm15, uint8(0 + 256));
    vpermilps(ymm1, ymm15, uint8(1 + 256));
    vpermilps(ymm2, ymm15, uint8(2 + 256));
    vpermilps(ymm3, ymm15, uint8(3 + 256));

    vpermilps(ymm4, ymm15, uint8(0 + 256) << 2);
    vpermilps(ymm5, ymm15, uint8(1 + 256) << 2);
    vpermilps(ymm6, ymm15, uint8(2 + 256) << 2);
    vpermilps(ymm7, ymm15, uint8(3 + 256) << 2);

    vpermilps(ymm8, ymm8, uint8(3 + 256) << 2);
    vpermilps(ymm9, ymm9, uint8(3 + 256) << 2);
    vpermilps(ymm10, ymm10, uint8(3 + 256) << 2);
    vpermilps(ymm11, ymm11, uint8(3 + 256) << 2);
    vpermilps(ymm12, ymm13, uint8(1 + 256) << 0);
    vpermilps(ymm13, ymm13, uint8(1 + 256) << 0);
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
