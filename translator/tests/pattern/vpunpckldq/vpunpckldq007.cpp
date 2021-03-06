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

    inputPredReg[1] = (1 << 0);
    inputPredReg[2] = (1 << 0) | (1 << 7) |           /* x86_64 */
                      (1 << 0) | (uint64_t(1) << 28); /* aarch64 */
    inputPredReg[3] = (1 << 0) | (1 << 7) | (1 << 11) |
                      (uint64_t(1) << 15) | /* x86_64 */
                      (1 << 0) | (uint64_t(1) << 28) | (uint64_t(1) << 44) |
                      (uint64_t(1) << 60); /* aarch64 */
    inputPredReg[4] = (1 << 0) | (1 << 7) | (1 << 11) | (1 << 13) |
                      (uint64_t(1) << 15) | /* x86_64 */
                      (1 << 0) | (uint64_t(1) << 28) | (uint64_t(1) << 44) |
                      (uint64_t(1) << 52) | (uint64_t(1) << 60); /* aarch64 */
    inputPredReg[5] = (1 << 0) | (1 << 9) | (1 << 11) | (1 << 13) | (1 << 14) |
                      (uint64_t(1) << 15) | /* x86_64 */
                      (1 << 0) | (uint64_t(1) << 36) | (uint64_t(1) << 44) |
                      (uint64_t(1) << 52) | (uint64_t(1) << 56) |
                      (uint64_t(1) << 60); /* aarch64 */
    inputPredReg[6] = (1 << 0) | (1 << 9) | (1 << 10) | (1 << 11) | (1 << 13) |
                      (uint64_t(1) << 14) | (uint64_t(1) << 15) | /* x86_64 */
                      (1 << 0) | (uint64_t(1) << 36) | (uint64_t(1) << 40) |
                      (uint64_t(1) << 44) | (uint64_t(1) << 52) |
                      (uint64_t(1) << 56) | (uint64_t(1) << 60); /* aarch64 */
    inputPredReg[7] = ~uint64_t(0);
  }

  void setCheckRegFlagAll() {
    /* Here modify arrays of checkGenRegMode, checkPredRegMode, checkZRegMode */
  }

  void genJitTestCode() {
    /* Here write JIT code with x86_64 mnemonic function to be tested. */
    vpunpckldq(Zmm(1) | k1, Zmm(30), Zmm(31));
    vpunpckldq(Zmm(2) | k2, Zmm(2), Zmm(31));
    vpunpckldq(Zmm(3) | k3, Zmm(31), Zmm(31));
    vpunpckldq(Zmm(4) | k4, Zmm(30), Zmm(4));
    vpunpckldq(Zmm(5) | k5, Zmm(5), Zmm(5));
    vpunpckldq(Zmm(6) | k6, Zmm(30), Zmm(31));
    vpunpckldq(Zmm(7) | k7, Zmm(30), Zmm(31));
    /*
    vpunpckldq(Zmm(8) | k1, Zmm(8), Zmm(31));
    vpunpckldq(Zmm(9) | k2, Zmm(9), Zmm(31));
    vpunpckldq(Zmm(10) | k3, Zmm(10), Zmm(31));
    vpunpckldq(Zmm(11) | k4, Zmm(11), Zmm(31));
    vpunpckldq(Zmm(12) | k5, Zmm(12), Zmm(31));
    vpunpckldq(Zmm(13) | k6, Zmm(13), Zmm(31));
    vpunpckldq(Zmm(14) | k7, Zmm(14), Zmm(31));

    vpunpckldq(Zmm(15) | k1, Zmm(30), Zmm(15));
    vpunpckldq(Zmm(16) | k2, Zmm(30), Zmm(16));
    vpunpckldq(Zmm(17) | k3, Zmm(30), Zmm(17));
    vpunpckldq(Zmm(18) | k4, Zmm(30), Zmm(18));
    vpunpckldq(Zmm(19) | k5, Zmm(30), Zmm(19));
    vpunpckldq(Zmm(20) | k6, Zmm(30), Zmm(20));
    vpunpckldq(Zmm(21) | k7, Zmm(30), Zmm(21));
    */
    vpunpckldq(Zmm(22) | k1, Zmm(22), Zmm(20));
    vpunpckldq(Zmm(23) | k2, Zmm(20), Zmm(20));
    vpunpckldq(Zmm(24) | k3, Zmm(20), Zmm(24));
    vpunpckldq(Zmm(25) | k4, Zmm(20), Zmm(21));
    vpunpckldq(Zmm(26) | k5, Zmm(26), Zmm(26));
    vpunpckldq(Zmm(27) | k6, Zmm(27), Zmm(27));
    vpunpckldq(Zmm(28) | k7, Zmm(28), Zmm(28));
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
