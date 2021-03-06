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
#if 0
    for (int i = 0; i < 8; i++) {
      inputZReg[0].ud_dt[i] = ~uint64_t(0);
      inputZReg[3].ud_dt[i] = ~uint64_t(0);
      inputZReg[6].ud_dt[i] = ~uint64_t(0);
    }
    for (int i = 0; i < 8; i++) {
      inputZReg[1].ud_dt[i] = uint32_t(0xFF00FF00AA55AA55);
      inputZReg[4].ud_dt[i] = uint32_t(0xFF00FF00AA55AA55);
      inputZReg[7].ud_dt[i] = uint32_t(0xFF00FF00AA55AA55);
    }
#endif
    inputPredReg[1] = 0x5555;
    inputPredReg[2] = 0xaaaa;
    inputPredReg[3] = 0xffff;
    inputPredReg[4] = 0x5a5a;
    inputPredReg[7] = 0xa5a5;
  }

  void setCheckRegFlagAll() {
    /* Here modify arrays of checkGenRegMode, checkPredRegMode, checkZRegMode */
  }

  void genJitTestCode() {
    /* Here write JIT code with x86_64 mnemonic function to be tested. */
    size_t addr1, addr2, addr3, addr4, addr5;
    size_t addr6, addr7, addr8, addr9, addr10;
    size_t addr11, addr12, addr13, addr14, addr15;
    addr1 = reinterpret_cast<size_t>(&(inputZReg[1].sp_dt[0])) + 1;
    addr2 = reinterpret_cast<size_t>(&(inputZReg[4].sp_dt[0])) + 3;
    addr3 = reinterpret_cast<size_t>(&(inputZReg[7].sp_dt[0])) + 5;
    addr4 = reinterpret_cast<size_t>(&(inputZReg[6].sp_dt[0])) + 1;
    addr5 = reinterpret_cast<size_t>(&(inputZReg[7].sp_dt[0])) + 3;
    addr6 = reinterpret_cast<size_t>(&(inputZReg[11].sp_dt[0])) + 5;
    addr7 = reinterpret_cast<size_t>(&(inputZReg[13].sp_dt[0])) + 1;
    addr8 = reinterpret_cast<size_t>(&(inputZReg[16].sp_dt[0])) + 3;
    addr9 = reinterpret_cast<size_t>(&(inputZReg[18].sp_dt[0])) + 5;
    addr10 = reinterpret_cast<size_t>(&(inputZReg[21].sp_dt[0])) + 1;
    addr11 = reinterpret_cast<size_t>(&(inputZReg[24].sp_dt[0])) + 3;
    addr12 = reinterpret_cast<size_t>(&(inputZReg[26].sp_dt[0])) + 5;
    addr13 = reinterpret_cast<size_t>(&(inputZReg[29].sp_dt[0])) + 1;
    addr14 = reinterpret_cast<size_t>(&(inputZReg[30].sp_dt[0])) + 3;
    addr15 = reinterpret_cast<size_t>(&(inputZReg[31].sp_dt[0])) + 5;

    mov(rax, addr1);
    vpxord(Xmm(2) | k1 | T_z, Xmm(0), ptr[rax]);
    mov(rax, addr2);
    vpxord(Ymm(5) | k1 | T_z, Ymm(3), ptr[rax]);
    mov(rax, addr3);
    vpxord(Zmm(8) | k1 | T_z, Zmm(6), ptr[rax]);

    mov(rax, addr4);
    vpxord(Xmm(6) | k2 | T_z, Xmm(7), ptr[rax]);
    mov(rax, addr5);
    vpxord(Xmm(8) | k3 | T_z, Xmm(9), ptr[rax]);
    mov(rax, addr6);
    vpxord(Xmm(10) | k4 | T_z, Xmm(10), ptr[rax]);

    mov(rax, addr7);
    vpxord(Ymm(13) | k2 | T_z, Ymm(14), ptr[rax]);
    mov(rax, addr8);
    vpxord(Ymm(15) | k3 | T_z, Ymm(16), ptr[rax]);
    mov(rax, addr9);
    vpxord(Ymm(17) | k4 | T_z, Ymm(17), ptr[rax]);

    mov(rax, addr10);
    vpxord(Zmm(21) | k2 | T_z, Zmm(22), ptr[rax]);
    mov(rax, addr11);
    vpxord(Zmm(23) | k3 | T_z, Zmm(24), ptr[rax]);
    mov(rax, addr12);
    vpxord(Zmm(25) | k4 | T_z, Zmm(25), ptr[rax]);

    mov(rax, addr13);
    vpxord(Xmm(29) | k1 | T_z, Xmm(29), ptr[rax]);
    mov(rax, addr14);
    vpxord(Ymm(30) | k1 | T_z, Ymm(30), ptr[rax]);
    mov(rax, addr15);
    vpxord(Zmm(31) | k1 | T_z, Zmm(31), ptr[rax]);

    mov(rax, 5);
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
