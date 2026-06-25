
virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs)
{
    FAUSTFLOAT* input0_ptr  = inputs[0];
    FAUSTFLOAT* input1_ptr  = inputs[1];
    FAUSTFLOAT* output0_ptr = outputs[0];
    FAUSTFLOAT* output1_ptr = outputs[1];
    double      fSlow0      = 0.4 * static_cast<double>(fHslider0);
    double      fSlow1      = 1.0 - fSlow0;
    double      fRec9_tmp[36];
    double*     fRec9  = &fRec9_tmp[4];
    double      fSlow2 = 0.28 * static_cast<double>(fHslider1) + 0.7;
    double      fZec0[32];
    double      fRec8_tmp[36];
    double*     fRec8 = &fRec8_tmp[4];
    double      fRec11_tmp[36];
    double*     fRec11 = &fRec11_tmp[4];
    double      fRec10_tmp[36];
    double*     fRec10 = &fRec10_tmp[4];
    double      fRec13_tmp[36];
    double*     fRec13 = &fRec13_tmp[4];
    double      fRec12_tmp[36];
    double*     fRec12 = &fRec12_tmp[4];
    double      fRec15_tmp[36];
    double*     fRec15 = &fRec15_tmp[4];
    double      fRec14_tmp[36];
    double*     fRec14 = &fRec14_tmp[4];
    double      fRec17_tmp[36];
    double*     fRec17 = &fRec17_tmp[4];
    double      fRec16_tmp[36];
    double*     fRec16 = &fRec16_tmp[4];
    double      fRec19_tmp[36];
    double*     fRec19 = &fRec19_tmp[4];
    double      fRec18_tmp[36];
    double*     fRec18 = &fRec18_tmp[4];
    double      fRec21_tmp[36];
    double*     fRec21 = &fRec21_tmp[4];
    double      fRec20_tmp[36];
    double*     fRec20 = &fRec20_tmp[4];
    double      fRec23_tmp[36];
    double*     fRec23 = &fRec23_tmp[4];
    double      fRec22_tmp[36];
    double*     fRec22 = &fRec22_tmp[4];
    double      fZec1[32];
    double      fRec6_tmp[36];
    double*     fRec6 = &fRec6_tmp[4];
    double      fRec7[32];
    double      fRec4_tmp[36];
    double*     fRec4 = &fRec4_tmp[4];
    double      fRec5[32];
    double      fRec2_tmp[36];
    double*     fRec2 = &fRec2_tmp[4];
    double      fRec3[32];
    double      fRec0_tmp[36];
    double*     fRec0 = &fRec0_tmp[4];
    double      fRec1[32];
    double      fSlow3 = static_cast<double>(fHslider2);
    double      fSlow4 = 1.0 - fSlow3;
    double      fRec33_tmp[36];
    double*     fRec33 = &fRec33_tmp[4];
    double      fRec32_tmp[36];
    double*     fRec32 = &fRec32_tmp[4];
    double      fRec35_tmp[36];
    double*     fRec35 = &fRec35_tmp[4];
    double      fRec34_tmp[36];
    double*     fRec34 = &fRec34_tmp[4];
    double      fRec37_tmp[36];
    double*     fRec37 = &fRec37_tmp[4];
    double      fRec36_tmp[36];
    double*     fRec36 = &fRec36_tmp[4];
    double      fRec39_tmp[36];
    double*     fRec39 = &fRec39_tmp[4];
    double      fRec38_tmp[36];
    double*     fRec38 = &fRec38_tmp[4];
    double      fRec41_tmp[36];
    double*     fRec41 = &fRec41_tmp[4];
    double      fRec40_tmp[36];
    double*     fRec40 = &fRec40_tmp[4];
    double      fRec43_tmp[36];
    double*     fRec43 = &fRec43_tmp[4];
    double      fRec42_tmp[36];
    double*     fRec42 = &fRec42_tmp[4];
    double      fRec45_tmp[36];
    double*     fRec45 = &fRec45_tmp[4];
    double      fRec44_tmp[36];
    double*     fRec44 = &fRec44_tmp[4];
    double      fRec47_tmp[36];
    double*     fRec47 = &fRec47_tmp[4];
    double      fRec46_tmp[36];
    double*     fRec46 = &fRec46_tmp[4];
    double      fZec2[32];
    double      fRec30_tmp[36];
    double*     fRec30 = &fRec30_tmp[4];
    double      fRec31[32];
    double      fRec28_tmp[36];
    double*     fRec28 = &fRec28_tmp[4];
    double      fRec29[32];
    double      fRec26_tmp[36];
    double*     fRec26 = &fRec26_tmp[4];
    double      fRec27[32];
    double      fRec24_tmp[36];
    double*     fRec24 = &fRec24_tmp[4];
    double      fRec25[32];
    int         vindex = 0;
    /* Main loop */
    for (vindex = 0; vindex <= (count - 32); vindex = vindex + 32) {
        FAUSTFLOAT* input0  = &input0_ptr[vindex];
        FAUSTFLOAT* input1  = &input1_ptr[vindex];
        FAUSTFLOAT* output0 = &output0_ptr[vindex];
        FAUSTFLOAT* output1 = &output1_ptr[vindex];
        int         vsize   = 32;
        /* Vectorizable loop 0 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec0[i] = 0.015 * (static_cast<double>(input0[i]) + static_cast<double>(input1[i]));
        }
        /* Recursive loop 1 */
        /* Pre code */
        for (int j0 = 0; j0 < 4; j0 = j0 + 1) {
            fRec9_tmp[j0] = fRec9_perm[j0];
        }
        fYec0_idx = (fYec0_idx + fYec0_idx_save) & 2047;
        for (int j2 = 0; j2 < 4; j2 = j2 + 1) {
            fRec8_tmp[j2] = fRec8_perm[j2];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec9[i]                      = fSlow0 * fRec9[i - 1] + fSlow1 * fRec8[i - 1];
            fYec0[(i + fYec0_idx) & 2047] = fSlow2 * fRec9[i] + fZec0[i];
            fRec8[i]                      = fYec0[(i + fYec0_idx - 1116) & 2047];
        }
        /* Post code */
        fYec0_idx_save = vsize;
        for (int j1 = 0; j1 < 4; j1 = j1 + 1) {
            fRec9_perm[j1] = fRec9_tmp[vsize + j1];
        }
        for (int j3 = 0; j3 < 4; j3 = j3 + 1) {
            fRec8_perm[j3] = fRec8_tmp[vsize + j3];
        }
        /* Recursive loop 2 */
        /* Pre code */
        for (int j4 = 0; j4 < 4; j4 = j4 + 1) {
            fRec11_tmp[j4] = fRec11_perm[j4];
        }
        fYec1_idx = (fYec1_idx + fYec1_idx_save) & 2047;
        for (int j6 = 0; j6 < 4; j6 = j6 + 1) {
            fRec10_tmp[j6] = fRec10_perm[j6];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec11[i]                     = fSlow0 * fRec11[i - 1] + fSlow1 * fRec10[i - 1];
            fYec1[(i + fYec1_idx) & 2047] = fZec0[i] + fSlow2 * fRec11[i];
            fRec10[i]                     = fYec1[(i + fYec1_idx - 1188) & 2047];
        }
        /* Post code */
        fYec1_idx_save = vsize;
        for (int j5 = 0; j5 < 4; j5 = j5 + 1) {
            fRec11_perm[j5] = fRec11_tmp[vsize + j5];
        }
        for (int j7 = 0; j7 < 4; j7 = j7 + 1) {
            fRec10_perm[j7] = fRec10_tmp[vsize + j7];
        }
        /* Recursive loop 3 */
        /* Pre code */
        for (int j8 = 0; j8 < 4; j8 = j8 + 1) {
            fRec13_tmp[j8] = fRec13_perm[j8];
        }
        fYec2_idx = (fYec2_idx + fYec2_idx_save) & 2047;
        for (int j10 = 0; j10 < 4; j10 = j10 + 1) {
            fRec12_tmp[j10] = fRec12_perm[j10];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec13[i]                     = fSlow0 * fRec13[i - 1] + fSlow1 * fRec12[i - 1];
            fYec2[(i + fYec2_idx) & 2047] = fZec0[i] + fSlow2 * fRec13[i];
            fRec12[i]                     = fYec2[(i + fYec2_idx - 1277) & 2047];
        }
        /* Post code */
        fYec2_idx_save = vsize;
        for (int j9 = 0; j9 < 4; j9 = j9 + 1) {
            fRec13_perm[j9] = fRec13_tmp[vsize + j9];
        }
        for (int j11 = 0; j11 < 4; j11 = j11 + 1) {
            fRec12_perm[j11] = fRec12_tmp[vsize + j11];
        }
        /* Recursive loop 4 */
        /* Pre code */
        for (int j12 = 0; j12 < 4; j12 = j12 + 1) {
            fRec15_tmp[j12] = fRec15_perm[j12];
        }
        fYec3_idx = (fYec3_idx + fYec3_idx_save) & 2047;
        for (int j14 = 0; j14 < 4; j14 = j14 + 1) {
            fRec14_tmp[j14] = fRec14_perm[j14];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec15[i]                     = fSlow0 * fRec15[i - 1] + fSlow1 * fRec14[i - 1];
            fYec3[(i + fYec3_idx) & 2047] = fZec0[i] + fSlow2 * fRec15[i];
            fRec14[i]                     = fYec3[(i + fYec3_idx - 1356) & 2047];
        }
        /* Post code */
        fYec3_idx_save = vsize;
        for (int j13 = 0; j13 < 4; j13 = j13 + 1) {
            fRec15_perm[j13] = fRec15_tmp[vsize + j13];
        }
        for (int j15 = 0; j15 < 4; j15 = j15 + 1) {
            fRec14_perm[j15] = fRec14_tmp[vsize + j15];
        }
        /* Recursive loop 5 */
        /* Pre code */
        for (int j16 = 0; j16 < 4; j16 = j16 + 1) {
            fRec17_tmp[j16] = fRec17_perm[j16];
        }
        fYec4_idx = (fYec4_idx + fYec4_idx_save) & 2047;
        for (int j18 = 0; j18 < 4; j18 = j18 + 1) {
            fRec16_tmp[j18] = fRec16_perm[j18];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec17[i]                     = fSlow0 * fRec17[i - 1] + fSlow1 * fRec16[i - 1];
            fYec4[(i + fYec4_idx) & 2047] = fZec0[i] + fSlow2 * fRec17[i];
            fRec16[i]                     = fYec4[(i + fYec4_idx - 1422) & 2047];
        }
        /* Post code */
        fYec4_idx_save = vsize;
        for (int j17 = 0; j17 < 4; j17 = j17 + 1) {
            fRec17_perm[j17] = fRec17_tmp[vsize + j17];
        }
        for (int j19 = 0; j19 < 4; j19 = j19 + 1) {
            fRec16_perm[j19] = fRec16_tmp[vsize + j19];
        }
        /* Recursive loop 6 */
        /* Pre code */
        for (int j20 = 0; j20 < 4; j20 = j20 + 1) {
            fRec19_tmp[j20] = fRec19_perm[j20];
        }
        fYec5_idx = (fYec5_idx + fYec5_idx_save) & 2047;
        for (int j22 = 0; j22 < 4; j22 = j22 + 1) {
            fRec18_tmp[j22] = fRec18_perm[j22];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec19[i]                     = fSlow0 * fRec19[i - 1] + fSlow1 * fRec18[i - 1];
            fYec5[(i + fYec5_idx) & 2047] = fZec0[i] + fSlow2 * fRec19[i];
            fRec18[i]                     = fYec5[(i + fYec5_idx - 1491) & 2047];
        }
        /* Post code */
        fYec5_idx_save = vsize;
        for (int j21 = 0; j21 < 4; j21 = j21 + 1) {
            fRec19_perm[j21] = fRec19_tmp[vsize + j21];
        }
        for (int j23 = 0; j23 < 4; j23 = j23 + 1) {
            fRec18_perm[j23] = fRec18_tmp[vsize + j23];
        }
        /* Recursive loop 7 */
        /* Pre code */
        for (int j24 = 0; j24 < 4; j24 = j24 + 1) {
            fRec21_tmp[j24] = fRec21_perm[j24];
        }
        fYec6_idx = (fYec6_idx + fYec6_idx_save) & 2047;
        for (int j26 = 0; j26 < 4; j26 = j26 + 1) {
            fRec20_tmp[j26] = fRec20_perm[j26];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec21[i]                     = fSlow0 * fRec21[i - 1] + fSlow1 * fRec20[i - 1];
            fYec6[(i + fYec6_idx) & 2047] = fZec0[i] + fSlow2 * fRec21[i];
            fRec20[i]                     = fYec6[(i + fYec6_idx - 1557) & 2047];
        }
        /* Post code */
        fYec6_idx_save = vsize;
        for (int j25 = 0; j25 < 4; j25 = j25 + 1) {
            fRec21_perm[j25] = fRec21_tmp[vsize + j25];
        }
        for (int j27 = 0; j27 < 4; j27 = j27 + 1) {
            fRec20_perm[j27] = fRec20_tmp[vsize + j27];
        }
        /* Recursive loop 8 */
        /* Pre code */
        for (int j28 = 0; j28 < 4; j28 = j28 + 1) {
            fRec23_tmp[j28] = fRec23_perm[j28];
        }
        fYec7_idx = (fYec7_idx + fYec7_idx_save) & 2047;
        for (int j30 = 0; j30 < 4; j30 = j30 + 1) {
            fRec22_tmp[j30] = fRec22_perm[j30];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec23[i]                     = fSlow0 * fRec23[i - 1] + fSlow1 * fRec22[i - 1];
            fYec7[(i + fYec7_idx) & 2047] = fZec0[i] + fSlow2 * fRec23[i];
            fRec22[i]                     = fYec7[(i + fYec7_idx - 1617) & 2047];
        }
        /* Post code */
        fYec7_idx_save = vsize;
        for (int j29 = 0; j29 < 4; j29 = j29 + 1) {
            fRec23_perm[j29] = fRec23_tmp[vsize + j29];
        }
        for (int j31 = 0; j31 < 4; j31 = j31 + 1) {
            fRec22_perm[j31] = fRec22_tmp[vsize + j31];
        }
        /* Recursive loop 9 */
        /* Pre code */
        for (int j40 = 0; j40 < 4; j40 = j40 + 1) {
            fRec33_tmp[j40] = fRec33_perm[j40];
        }
        fYec12_idx = (fYec12_idx + fYec12_idx_save) & 2047;
        for (int j42 = 0; j42 < 4; j42 = j42 + 1) {
            fRec32_tmp[j42] = fRec32_perm[j42];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec33[i]                       = fSlow0 * fRec33[i - 1] + fSlow1 * fRec32[i - 1];
            fYec12[(i + fYec12_idx) & 2047] = fZec0[i] + fSlow2 * fRec33[i];
            fRec32[i]                       = fYec12[(i + fYec12_idx - 1139) & 2047];
        }
        /* Post code */
        fYec12_idx_save = vsize;
        for (int j41 = 0; j41 < 4; j41 = j41 + 1) {
            fRec33_perm[j41] = fRec33_tmp[vsize + j41];
        }
        for (int j43 = 0; j43 < 4; j43 = j43 + 1) {
            fRec32_perm[j43] = fRec32_tmp[vsize + j43];
        }
        /* Recursive loop 10 */
        /* Pre code */
        for (int j44 = 0; j44 < 4; j44 = j44 + 1) {
            fRec35_tmp[j44] = fRec35_perm[j44];
        }
        fYec13_idx = (fYec13_idx + fYec13_idx_save) & 2047;
        for (int j46 = 0; j46 < 4; j46 = j46 + 1) {
            fRec34_tmp[j46] = fRec34_perm[j46];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec35[i]                       = fSlow0 * fRec35[i - 1] + fSlow1 * fRec34[i - 1];
            fYec13[(i + fYec13_idx) & 2047] = fZec0[i] + fSlow2 * fRec35[i];
            fRec34[i]                       = fYec13[(i + fYec13_idx - 1211) & 2047];
        }
        /* Post code */
        fYec13_idx_save = vsize;
        for (int j45 = 0; j45 < 4; j45 = j45 + 1) {
            fRec35_perm[j45] = fRec35_tmp[vsize + j45];
        }
        for (int j47 = 0; j47 < 4; j47 = j47 + 1) {
            fRec34_perm[j47] = fRec34_tmp[vsize + j47];
        }
        /* Recursive loop 11 */
        /* Pre code */
        for (int j48 = 0; j48 < 4; j48 = j48 + 1) {
            fRec37_tmp[j48] = fRec37_perm[j48];
        }
        fYec14_idx = (fYec14_idx + fYec14_idx_save) & 2047;
        for (int j50 = 0; j50 < 4; j50 = j50 + 1) {
            fRec36_tmp[j50] = fRec36_perm[j50];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec37[i]                       = fSlow0 * fRec37[i - 1] + fSlow1 * fRec36[i - 1];
            fYec14[(i + fYec14_idx) & 2047] = fZec0[i] + fSlow2 * fRec37[i];
            fRec36[i]                       = fYec14[(i + fYec14_idx - 1300) & 2047];
        }
        /* Post code */
        fYec14_idx_save = vsize;
        for (int j49 = 0; j49 < 4; j49 = j49 + 1) {
            fRec37_perm[j49] = fRec37_tmp[vsize + j49];
        }
        for (int j51 = 0; j51 < 4; j51 = j51 + 1) {
            fRec36_perm[j51] = fRec36_tmp[vsize + j51];
        }
        /* Recursive loop 12 */
        /* Pre code */
        for (int j52 = 0; j52 < 4; j52 = j52 + 1) {
            fRec39_tmp[j52] = fRec39_perm[j52];
        }
        fYec15_idx = (fYec15_idx + fYec15_idx_save) & 2047;
        for (int j54 = 0; j54 < 4; j54 = j54 + 1) {
            fRec38_tmp[j54] = fRec38_perm[j54];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec39[i]                       = fSlow0 * fRec39[i - 1] + fSlow1 * fRec38[i - 1];
            fYec15[(i + fYec15_idx) & 2047] = fZec0[i] + fSlow2 * fRec39[i];
            fRec38[i]                       = fYec15[(i + fYec15_idx - 1379) & 2047];
        }
        /* Post code */
        fYec15_idx_save = vsize;
        for (int j53 = 0; j53 < 4; j53 = j53 + 1) {
            fRec39_perm[j53] = fRec39_tmp[vsize + j53];
        }
        for (int j55 = 0; j55 < 4; j55 = j55 + 1) {
            fRec38_perm[j55] = fRec38_tmp[vsize + j55];
        }
        /* Recursive loop 13 */
        /* Pre code */
        for (int j56 = 0; j56 < 4; j56 = j56 + 1) {
            fRec41_tmp[j56] = fRec41_perm[j56];
        }
        fYec16_idx = (fYec16_idx + fYec16_idx_save) & 2047;
        for (int j58 = 0; j58 < 4; j58 = j58 + 1) {
            fRec40_tmp[j58] = fRec40_perm[j58];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec41[i]                       = fSlow0 * fRec41[i - 1] + fSlow1 * fRec40[i - 1];
            fYec16[(i + fYec16_idx) & 2047] = fZec0[i] + fSlow2 * fRec41[i];
            fRec40[i]                       = fYec16[(i + fYec16_idx - 1445) & 2047];
        }
        /* Post code */
        fYec16_idx_save = vsize;
        for (int j57 = 0; j57 < 4; j57 = j57 + 1) {
            fRec41_perm[j57] = fRec41_tmp[vsize + j57];
        }
        for (int j59 = 0; j59 < 4; j59 = j59 + 1) {
            fRec40_perm[j59] = fRec40_tmp[vsize + j59];
        }
        /* Recursive loop 14 */
        /* Pre code */
        for (int j60 = 0; j60 < 4; j60 = j60 + 1) {
            fRec43_tmp[j60] = fRec43_perm[j60];
        }
        fYec17_idx = (fYec17_idx + fYec17_idx_save) & 2047;
        for (int j62 = 0; j62 < 4; j62 = j62 + 1) {
            fRec42_tmp[j62] = fRec42_perm[j62];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec43[i]                       = fSlow0 * fRec43[i - 1] + fSlow1 * fRec42[i - 1];
            fYec17[(i + fYec17_idx) & 2047] = fZec0[i] + fSlow2 * fRec43[i];
            fRec42[i]                       = fYec17[(i + fYec17_idx - 1514) & 2047];
        }
        /* Post code */
        fYec17_idx_save = vsize;
        for (int j61 = 0; j61 < 4; j61 = j61 + 1) {
            fRec43_perm[j61] = fRec43_tmp[vsize + j61];
        }
        for (int j63 = 0; j63 < 4; j63 = j63 + 1) {
            fRec42_perm[j63] = fRec42_tmp[vsize + j63];
        }
        /* Recursive loop 15 */
        /* Pre code */
        for (int j64 = 0; j64 < 4; j64 = j64 + 1) {
            fRec45_tmp[j64] = fRec45_perm[j64];
        }
        fYec18_idx = (fYec18_idx + fYec18_idx_save) & 2047;
        for (int j66 = 0; j66 < 4; j66 = j66 + 1) {
            fRec44_tmp[j66] = fRec44_perm[j66];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec45[i]                       = fSlow0 * fRec45[i - 1] + fSlow1 * fRec44[i - 1];
            fYec18[(i + fYec18_idx) & 2047] = fZec0[i] + fSlow2 * fRec45[i];
            fRec44[i]                       = fYec18[(i + fYec18_idx - 1580) & 2047];
        }
        /* Post code */
        fYec18_idx_save = vsize;
        for (int j65 = 0; j65 < 4; j65 = j65 + 1) {
            fRec45_perm[j65] = fRec45_tmp[vsize + j65];
        }
        for (int j67 = 0; j67 < 4; j67 = j67 + 1) {
            fRec44_perm[j67] = fRec44_tmp[vsize + j67];
        }
        /* Recursive loop 16 */
        /* Pre code */
        for (int j68 = 0; j68 < 4; j68 = j68 + 1) {
            fRec47_tmp[j68] = fRec47_perm[j68];
        }
        fYec19_idx = (fYec19_idx + fYec19_idx_save) & 2047;
        for (int j70 = 0; j70 < 4; j70 = j70 + 1) {
            fRec46_tmp[j70] = fRec46_perm[j70];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec47[i]                       = fSlow0 * fRec47[i - 1] + fSlow1 * fRec46[i - 1];
            fYec19[(i + fYec19_idx) & 2047] = fZec0[i] + fSlow2 * fRec47[i];
            fRec46[i]                       = fYec19[(i + fYec19_idx - 1640) & 2047];
        }
        /* Post code */
        fYec19_idx_save = vsize;
        for (int j69 = 0; j69 < 4; j69 = j69 + 1) {
            fRec47_perm[j69] = fRec47_tmp[vsize + j69];
        }
        for (int j71 = 0; j71 < 4; j71 = j71 + 1) {
            fRec46_perm[j71] = fRec46_tmp[vsize + j71];
        }
        /* Vectorizable loop 17 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec1[i] = fRec8[i] + fRec10[i] + fRec12[i] + fRec14[i] + fRec16[i] + fRec18[i] +
                       fRec20[i] + fRec22[i];
        }
        /* Vectorizable loop 18 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec2[i] = fRec32[i] + fRec34[i] + fRec36[i] + fRec38[i] + fRec40[i] + fRec42[i] +
                       fRec44[i] + fRec46[i];
        }
        /* Recursive loop 19 */
        /* Pre code */
        fYec8_idx = (fYec8_idx + fYec8_idx_save) & 1023;
        for (int j32 = 0; j32 < 4; j32 = j32 + 1) {
            fRec6_tmp[j32] = fRec6_perm[j32];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec8[(i + fYec8_idx) & 1023] = fZec1[i] + 0.5 * fRec6[i - 1];
            fRec6[i]                      = fYec8[(i + fYec8_idx - 556) & 1023];
            fRec7[i]                      = fRec6[i - 1] - fZec1[i];
        }
        /* Post code */
        fYec8_idx_save = vsize;
        for (int j33 = 0; j33 < 4; j33 = j33 + 1) {
            fRec6_perm[j33] = fRec6_tmp[vsize + j33];
        }
        /* Recursive loop 20 */
        /* Pre code */
        fYec20_idx = (fYec20_idx + fYec20_idx_save) & 1023;
        for (int j72 = 0; j72 < 4; j72 = j72 + 1) {
            fRec30_tmp[j72] = fRec30_perm[j72];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec20[(i + fYec20_idx) & 1023] = fZec2[i] + 0.5 * fRec30[i - 1];
            fRec30[i]                       = fYec20[(i + fYec20_idx - 579) & 1023];
            fRec31[i]                       = fRec30[i - 1] - fZec2[i];
        }
        /* Post code */
        fYec20_idx_save = vsize;
        for (int j73 = 0; j73 < 4; j73 = j73 + 1) {
            fRec30_perm[j73] = fRec30_tmp[vsize + j73];
        }
        /* Recursive loop 21 */
        /* Pre code */
        fYec9_idx = (fYec9_idx + fYec9_idx_save) & 511;
        for (int j34 = 0; j34 < 4; j34 = j34 + 1) {
            fRec4_tmp[j34] = fRec4_perm[j34];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec9[(i + fYec9_idx) & 511] = fRec7[i] + 0.5 * fRec4[i - 1];
            fRec4[i]                     = fYec9[(i + fYec9_idx - 441) & 511];
            fRec5[i]                     = fRec4[i - 1] - fRec7[i];
        }
        /* Post code */
        fYec9_idx_save = vsize;
        for (int j35 = 0; j35 < 4; j35 = j35 + 1) {
            fRec4_perm[j35] = fRec4_tmp[vsize + j35];
        }
        /* Recursive loop 22 */
        /* Pre code */
        fYec21_idx = (fYec21_idx + fYec21_idx_save) & 511;
        for (int j74 = 0; j74 < 4; j74 = j74 + 1) {
            fRec28_tmp[j74] = fRec28_perm[j74];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec21[(i + fYec21_idx) & 511] = fRec31[i] + 0.5 * fRec28[i - 1];
            fRec28[i]                      = fYec21[(i + fYec21_idx - 464) & 511];
            fRec29[i]                      = fRec28[i - 1] - fRec31[i];
        }
        /* Post code */
        fYec21_idx_save = vsize;
        for (int j75 = 0; j75 < 4; j75 = j75 + 1) {
            fRec28_perm[j75] = fRec28_tmp[vsize + j75];
        }
        /* Recursive loop 23 */
        /* Pre code */
        fYec10_idx = (fYec10_idx + fYec10_idx_save) & 511;
        for (int j36 = 0; j36 < 4; j36 = j36 + 1) {
            fRec2_tmp[j36] = fRec2_perm[j36];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec10[(i + fYec10_idx) & 511] = fRec5[i] + 0.5 * fRec2[i - 1];
            fRec2[i]                       = fYec10[(i + fYec10_idx - 341) & 511];
            fRec3[i]                       = fRec2[i - 1] - fRec5[i];
        }
        /* Post code */
        fYec10_idx_save = vsize;
        for (int j37 = 0; j37 < 4; j37 = j37 + 1) {
            fRec2_perm[j37] = fRec2_tmp[vsize + j37];
        }
        /* Recursive loop 24 */
        /* Pre code */
        fYec22_idx = (fYec22_idx + fYec22_idx_save) & 511;
        for (int j76 = 0; j76 < 4; j76 = j76 + 1) {
            fRec26_tmp[j76] = fRec26_perm[j76];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec22[(i + fYec22_idx) & 511] = fRec29[i] + 0.5 * fRec26[i - 1];
            fRec26[i]                      = fYec22[(i + fYec22_idx - 364) & 511];
            fRec27[i]                      = fRec26[i - 1] - fRec29[i];
        }
        /* Post code */
        fYec22_idx_save = vsize;
        for (int j77 = 0; j77 < 4; j77 = j77 + 1) {
            fRec26_perm[j77] = fRec26_tmp[vsize + j77];
        }
        /* Recursive loop 25 */
        /* Pre code */
        fYec11_idx = (fYec11_idx + fYec11_idx_save) & 511;
        for (int j38 = 0; j38 < 4; j38 = j38 + 1) {
            fRec0_tmp[j38] = fRec0_perm[j38];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec11[(i + fYec11_idx) & 511] = fRec3[i] + 0.5 * fRec0[i - 1];
            fRec0[i]                       = fYec11[(i + fYec11_idx - 225) & 511];
            fRec1[i]                       = fRec0[i - 1] - fRec3[i];
        }
        /* Post code */
        fYec11_idx_save = vsize;
        for (int j39 = 0; j39 < 4; j39 = j39 + 1) {
            fRec0_perm[j39] = fRec0_tmp[vsize + j39];
        }
        /* Recursive loop 26 */
        /* Pre code */
        fYec23_idx = (fYec23_idx + fYec23_idx_save) & 511;
        for (int j78 = 0; j78 < 4; j78 = j78 + 1) {
            fRec24_tmp[j78] = fRec24_perm[j78];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec23[(i + fYec23_idx) & 511] = fRec27[i] + 0.5 * fRec24[i - 1];
            fRec24[i]                      = fYec23[(i + fYec23_idx - 248) & 511];
            fRec25[i]                      = fRec24[i - 1] - fRec27[i];
        }
        /* Post code */
        fYec23_idx_save = vsize;
        for (int j79 = 0; j79 < 4; j79 = j79 + 1) {
            fRec24_perm[j79] = fRec24_tmp[vsize + j79];
        }
        /* Vectorizable loop 27 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            output0[i] = static_cast<FAUSTFLOAT>(fSlow3 * fRec1[i] +
                                                 fSlow4 * static_cast<double>(input0[i]));
        }
        /* Vectorizable loop 28 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            output1[i] = static_cast<FAUSTFLOAT>(fSlow3 * fRec25[i] +
                                                 fSlow4 * static_cast<double>(input1[i]));
        }
    }
    /* Remaining frames */
    if (vindex < count) {
        FAUSTFLOAT* input0  = &input0_ptr[vindex];
        FAUSTFLOAT* input1  = &input1_ptr[vindex];
        FAUSTFLOAT* output0 = &output0_ptr[vindex];
        FAUSTFLOAT* output1 = &output1_ptr[vindex];
        int         vsize   = count - vindex;
        /* Vectorizable loop 0 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec0[i] = 0.015 * (static_cast<double>(input0[i]) + static_cast<double>(input1[i]));
        }
        /* Recursive loop 1 */
        /* Pre code */
        for (int j0 = 0; j0 < 4; j0 = j0 + 1) {
            fRec9_tmp[j0] = fRec9_perm[j0];
        }
        fYec0_idx = (fYec0_idx + fYec0_idx_save) & 2047;
        for (int j2 = 0; j2 < 4; j2 = j2 + 1) {
            fRec8_tmp[j2] = fRec8_perm[j2];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec9[i]                      = fSlow0 * fRec9[i - 1] + fSlow1 * fRec8[i - 1];
            fYec0[(i + fYec0_idx) & 2047] = fSlow2 * fRec9[i] + fZec0[i];
            fRec8[i]                      = fYec0[(i + fYec0_idx - 1116) & 2047];
        }
        /* Post code */
        fYec0_idx_save = vsize;
        for (int j1 = 0; j1 < 4; j1 = j1 + 1) {
            fRec9_perm[j1] = fRec9_tmp[vsize + j1];
        }
        for (int j3 = 0; j3 < 4; j3 = j3 + 1) {
            fRec8_perm[j3] = fRec8_tmp[vsize + j3];
        }
        /* Recursive loop 2 */
        /* Pre code */
        for (int j4 = 0; j4 < 4; j4 = j4 + 1) {
            fRec11_tmp[j4] = fRec11_perm[j4];
        }
        fYec1_idx = (fYec1_idx + fYec1_idx_save) & 2047;
        for (int j6 = 0; j6 < 4; j6 = j6 + 1) {
            fRec10_tmp[j6] = fRec10_perm[j6];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec11[i]                     = fSlow0 * fRec11[i - 1] + fSlow1 * fRec10[i - 1];
            fYec1[(i + fYec1_idx) & 2047] = fZec0[i] + fSlow2 * fRec11[i];
            fRec10[i]                     = fYec1[(i + fYec1_idx - 1188) & 2047];
        }
        /* Post code */
        fYec1_idx_save = vsize;
        for (int j5 = 0; j5 < 4; j5 = j5 + 1) {
            fRec11_perm[j5] = fRec11_tmp[vsize + j5];
        }
        for (int j7 = 0; j7 < 4; j7 = j7 + 1) {
            fRec10_perm[j7] = fRec10_tmp[vsize + j7];
        }
        /* Recursive loop 3 */
        /* Pre code */
        for (int j8 = 0; j8 < 4; j8 = j8 + 1) {
            fRec13_tmp[j8] = fRec13_perm[j8];
        }
        fYec2_idx = (fYec2_idx + fYec2_idx_save) & 2047;
        for (int j10 = 0; j10 < 4; j10 = j10 + 1) {
            fRec12_tmp[j10] = fRec12_perm[j10];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec13[i]                     = fSlow0 * fRec13[i - 1] + fSlow1 * fRec12[i - 1];
            fYec2[(i + fYec2_idx) & 2047] = fZec0[i] + fSlow2 * fRec13[i];
            fRec12[i]                     = fYec2[(i + fYec2_idx - 1277) & 2047];
        }
        /* Post code */
        fYec2_idx_save = vsize;
        for (int j9 = 0; j9 < 4; j9 = j9 + 1) {
            fRec13_perm[j9] = fRec13_tmp[vsize + j9];
        }
        for (int j11 = 0; j11 < 4; j11 = j11 + 1) {
            fRec12_perm[j11] = fRec12_tmp[vsize + j11];
        }
        /* Recursive loop 4 */
        /* Pre code */
        for (int j12 = 0; j12 < 4; j12 = j12 + 1) {
            fRec15_tmp[j12] = fRec15_perm[j12];
        }
        fYec3_idx = (fYec3_idx + fYec3_idx_save) & 2047;
        for (int j14 = 0; j14 < 4; j14 = j14 + 1) {
            fRec14_tmp[j14] = fRec14_perm[j14];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec15[i]                     = fSlow0 * fRec15[i - 1] + fSlow1 * fRec14[i - 1];
            fYec3[(i + fYec3_idx) & 2047] = fZec0[i] + fSlow2 * fRec15[i];
            fRec14[i]                     = fYec3[(i + fYec3_idx - 1356) & 2047];
        }
        /* Post code */
        fYec3_idx_save = vsize;
        for (int j13 = 0; j13 < 4; j13 = j13 + 1) {
            fRec15_perm[j13] = fRec15_tmp[vsize + j13];
        }
        for (int j15 = 0; j15 < 4; j15 = j15 + 1) {
            fRec14_perm[j15] = fRec14_tmp[vsize + j15];
        }
        /* Recursive loop 5 */
        /* Pre code */
        for (int j16 = 0; j16 < 4; j16 = j16 + 1) {
            fRec17_tmp[j16] = fRec17_perm[j16];
        }
        fYec4_idx = (fYec4_idx + fYec4_idx_save) & 2047;
        for (int j18 = 0; j18 < 4; j18 = j18 + 1) {
            fRec16_tmp[j18] = fRec16_perm[j18];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec17[i]                     = fSlow0 * fRec17[i - 1] + fSlow1 * fRec16[i - 1];
            fYec4[(i + fYec4_idx) & 2047] = fZec0[i] + fSlow2 * fRec17[i];
            fRec16[i]                     = fYec4[(i + fYec4_idx - 1422) & 2047];
        }
        /* Post code */
        fYec4_idx_save = vsize;
        for (int j17 = 0; j17 < 4; j17 = j17 + 1) {
            fRec17_perm[j17] = fRec17_tmp[vsize + j17];
        }
        for (int j19 = 0; j19 < 4; j19 = j19 + 1) {
            fRec16_perm[j19] = fRec16_tmp[vsize + j19];
        }
        /* Recursive loop 6 */
        /* Pre code */
        for (int j20 = 0; j20 < 4; j20 = j20 + 1) {
            fRec19_tmp[j20] = fRec19_perm[j20];
        }
        fYec5_idx = (fYec5_idx + fYec5_idx_save) & 2047;
        for (int j22 = 0; j22 < 4; j22 = j22 + 1) {
            fRec18_tmp[j22] = fRec18_perm[j22];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec19[i]                     = fSlow0 * fRec19[i - 1] + fSlow1 * fRec18[i - 1];
            fYec5[(i + fYec5_idx) & 2047] = fZec0[i] + fSlow2 * fRec19[i];
            fRec18[i]                     = fYec5[(i + fYec5_idx - 1491) & 2047];
        }
        /* Post code */
        fYec5_idx_save = vsize;
        for (int j21 = 0; j21 < 4; j21 = j21 + 1) {
            fRec19_perm[j21] = fRec19_tmp[vsize + j21];
        }
        for (int j23 = 0; j23 < 4; j23 = j23 + 1) {
            fRec18_perm[j23] = fRec18_tmp[vsize + j23];
        }
        /* Recursive loop 7 */
        /* Pre code */
        for (int j24 = 0; j24 < 4; j24 = j24 + 1) {
            fRec21_tmp[j24] = fRec21_perm[j24];
        }
        fYec6_idx = (fYec6_idx + fYec6_idx_save) & 2047;
        for (int j26 = 0; j26 < 4; j26 = j26 + 1) {
            fRec20_tmp[j26] = fRec20_perm[j26];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec21[i]                     = fSlow0 * fRec21[i - 1] + fSlow1 * fRec20[i - 1];
            fYec6[(i + fYec6_idx) & 2047] = fZec0[i] + fSlow2 * fRec21[i];
            fRec20[i]                     = fYec6[(i + fYec6_idx - 1557) & 2047];
        }
        /* Post code */
        fYec6_idx_save = vsize;
        for (int j25 = 0; j25 < 4; j25 = j25 + 1) {
            fRec21_perm[j25] = fRec21_tmp[vsize + j25];
        }
        for (int j27 = 0; j27 < 4; j27 = j27 + 1) {
            fRec20_perm[j27] = fRec20_tmp[vsize + j27];
        }
        /* Recursive loop 8 */
        /* Pre code */
        for (int j28 = 0; j28 < 4; j28 = j28 + 1) {
            fRec23_tmp[j28] = fRec23_perm[j28];
        }
        fYec7_idx = (fYec7_idx + fYec7_idx_save) & 2047;
        for (int j30 = 0; j30 < 4; j30 = j30 + 1) {
            fRec22_tmp[j30] = fRec22_perm[j30];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec23[i]                     = fSlow0 * fRec23[i - 1] + fSlow1 * fRec22[i - 1];
            fYec7[(i + fYec7_idx) & 2047] = fZec0[i] + fSlow2 * fRec23[i];
            fRec22[i]                     = fYec7[(i + fYec7_idx - 1617) & 2047];
        }
        /* Post code */
        fYec7_idx_save = vsize;
        for (int j29 = 0; j29 < 4; j29 = j29 + 1) {
            fRec23_perm[j29] = fRec23_tmp[vsize + j29];
        }
        for (int j31 = 0; j31 < 4; j31 = j31 + 1) {
            fRec22_perm[j31] = fRec22_tmp[vsize + j31];
        }
        /* Recursive loop 9 */
        /* Pre code */
        for (int j40 = 0; j40 < 4; j40 = j40 + 1) {
            fRec33_tmp[j40] = fRec33_perm[j40];
        }
        fYec12_idx = (fYec12_idx + fYec12_idx_save) & 2047;
        for (int j42 = 0; j42 < 4; j42 = j42 + 1) {
            fRec32_tmp[j42] = fRec32_perm[j42];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec33[i]                       = fSlow0 * fRec33[i - 1] + fSlow1 * fRec32[i - 1];
            fYec12[(i + fYec12_idx) & 2047] = fZec0[i] + fSlow2 * fRec33[i];
            fRec32[i]                       = fYec12[(i + fYec12_idx - 1139) & 2047];
        }
        /* Post code */
        fYec12_idx_save = vsize;
        for (int j41 = 0; j41 < 4; j41 = j41 + 1) {
            fRec33_perm[j41] = fRec33_tmp[vsize + j41];
        }
        for (int j43 = 0; j43 < 4; j43 = j43 + 1) {
            fRec32_perm[j43] = fRec32_tmp[vsize + j43];
        }
        /* Recursive loop 10 */
        /* Pre code */
        for (int j44 = 0; j44 < 4; j44 = j44 + 1) {
            fRec35_tmp[j44] = fRec35_perm[j44];
        }
        fYec13_idx = (fYec13_idx + fYec13_idx_save) & 2047;
        for (int j46 = 0; j46 < 4; j46 = j46 + 1) {
            fRec34_tmp[j46] = fRec34_perm[j46];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec35[i]                       = fSlow0 * fRec35[i - 1] + fSlow1 * fRec34[i - 1];
            fYec13[(i + fYec13_idx) & 2047] = fZec0[i] + fSlow2 * fRec35[i];
            fRec34[i]                       = fYec13[(i + fYec13_idx - 1211) & 2047];
        }
        /* Post code */
        fYec13_idx_save = vsize;
        for (int j45 = 0; j45 < 4; j45 = j45 + 1) {
            fRec35_perm[j45] = fRec35_tmp[vsize + j45];
        }
        for (int j47 = 0; j47 < 4; j47 = j47 + 1) {
            fRec34_perm[j47] = fRec34_tmp[vsize + j47];
        }
        /* Recursive loop 11 */
        /* Pre code */
        for (int j48 = 0; j48 < 4; j48 = j48 + 1) {
            fRec37_tmp[j48] = fRec37_perm[j48];
        }
        fYec14_idx = (fYec14_idx + fYec14_idx_save) & 2047;
        for (int j50 = 0; j50 < 4; j50 = j50 + 1) {
            fRec36_tmp[j50] = fRec36_perm[j50];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec37[i]                       = fSlow0 * fRec37[i - 1] + fSlow1 * fRec36[i - 1];
            fYec14[(i + fYec14_idx) & 2047] = fZec0[i] + fSlow2 * fRec37[i];
            fRec36[i]                       = fYec14[(i + fYec14_idx - 1300) & 2047];
        }
        /* Post code */
        fYec14_idx_save = vsize;
        for (int j49 = 0; j49 < 4; j49 = j49 + 1) {
            fRec37_perm[j49] = fRec37_tmp[vsize + j49];
        }
        for (int j51 = 0; j51 < 4; j51 = j51 + 1) {
            fRec36_perm[j51] = fRec36_tmp[vsize + j51];
        }
        /* Recursive loop 12 */
        /* Pre code */
        for (int j52 = 0; j52 < 4; j52 = j52 + 1) {
            fRec39_tmp[j52] = fRec39_perm[j52];
        }
        fYec15_idx = (fYec15_idx + fYec15_idx_save) & 2047;
        for (int j54 = 0; j54 < 4; j54 = j54 + 1) {
            fRec38_tmp[j54] = fRec38_perm[j54];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec39[i]                       = fSlow0 * fRec39[i - 1] + fSlow1 * fRec38[i - 1];
            fYec15[(i + fYec15_idx) & 2047] = fZec0[i] + fSlow2 * fRec39[i];
            fRec38[i]                       = fYec15[(i + fYec15_idx - 1379) & 2047];
        }
        /* Post code */
        fYec15_idx_save = vsize;
        for (int j53 = 0; j53 < 4; j53 = j53 + 1) {
            fRec39_perm[j53] = fRec39_tmp[vsize + j53];
        }
        for (int j55 = 0; j55 < 4; j55 = j55 + 1) {
            fRec38_perm[j55] = fRec38_tmp[vsize + j55];
        }
        /* Recursive loop 13 */
        /* Pre code */
        for (int j56 = 0; j56 < 4; j56 = j56 + 1) {
            fRec41_tmp[j56] = fRec41_perm[j56];
        }
        fYec16_idx = (fYec16_idx + fYec16_idx_save) & 2047;
        for (int j58 = 0; j58 < 4; j58 = j58 + 1) {
            fRec40_tmp[j58] = fRec40_perm[j58];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec41[i]                       = fSlow0 * fRec41[i - 1] + fSlow1 * fRec40[i - 1];
            fYec16[(i + fYec16_idx) & 2047] = fZec0[i] + fSlow2 * fRec41[i];
            fRec40[i]                       = fYec16[(i + fYec16_idx - 1445) & 2047];
        }
        /* Post code */
        fYec16_idx_save = vsize;
        for (int j57 = 0; j57 < 4; j57 = j57 + 1) {
            fRec41_perm[j57] = fRec41_tmp[vsize + j57];
        }
        for (int j59 = 0; j59 < 4; j59 = j59 + 1) {
            fRec40_perm[j59] = fRec40_tmp[vsize + j59];
        }
        /* Recursive loop 14 */
        /* Pre code */
        for (int j60 = 0; j60 < 4; j60 = j60 + 1) {
            fRec43_tmp[j60] = fRec43_perm[j60];
        }
        fYec17_idx = (fYec17_idx + fYec17_idx_save) & 2047;
        for (int j62 = 0; j62 < 4; j62 = j62 + 1) {
            fRec42_tmp[j62] = fRec42_perm[j62];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec43[i]                       = fSlow0 * fRec43[i - 1] + fSlow1 * fRec42[i - 1];
            fYec17[(i + fYec17_idx) & 2047] = fZec0[i] + fSlow2 * fRec43[i];
            fRec42[i]                       = fYec17[(i + fYec17_idx - 1514) & 2047];
        }
        /* Post code */
        fYec17_idx_save = vsize;
        for (int j61 = 0; j61 < 4; j61 = j61 + 1) {
            fRec43_perm[j61] = fRec43_tmp[vsize + j61];
        }
        for (int j63 = 0; j63 < 4; j63 = j63 + 1) {
            fRec42_perm[j63] = fRec42_tmp[vsize + j63];
        }
        /* Recursive loop 15 */
        /* Pre code */
        for (int j64 = 0; j64 < 4; j64 = j64 + 1) {
            fRec45_tmp[j64] = fRec45_perm[j64];
        }
        fYec18_idx = (fYec18_idx + fYec18_idx_save) & 2047;
        for (int j66 = 0; j66 < 4; j66 = j66 + 1) {
            fRec44_tmp[j66] = fRec44_perm[j66];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec45[i]                       = fSlow0 * fRec45[i - 1] + fSlow1 * fRec44[i - 1];
            fYec18[(i + fYec18_idx) & 2047] = fZec0[i] + fSlow2 * fRec45[i];
            fRec44[i]                       = fYec18[(i + fYec18_idx - 1580) & 2047];
        }
        /* Post code */
        fYec18_idx_save = vsize;
        for (int j65 = 0; j65 < 4; j65 = j65 + 1) {
            fRec45_perm[j65] = fRec45_tmp[vsize + j65];
        }
        for (int j67 = 0; j67 < 4; j67 = j67 + 1) {
            fRec44_perm[j67] = fRec44_tmp[vsize + j67];
        }
        /* Recursive loop 16 */
        /* Pre code */
        for (int j68 = 0; j68 < 4; j68 = j68 + 1) {
            fRec47_tmp[j68] = fRec47_perm[j68];
        }
        fYec19_idx = (fYec19_idx + fYec19_idx_save) & 2047;
        for (int j70 = 0; j70 < 4; j70 = j70 + 1) {
            fRec46_tmp[j70] = fRec46_perm[j70];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec47[i]                       = fSlow0 * fRec47[i - 1] + fSlow1 * fRec46[i - 1];
            fYec19[(i + fYec19_idx) & 2047] = fZec0[i] + fSlow2 * fRec47[i];
            fRec46[i]                       = fYec19[(i + fYec19_idx - 1640) & 2047];
        }
        /* Post code */
        fYec19_idx_save = vsize;
        for (int j69 = 0; j69 < 4; j69 = j69 + 1) {
            fRec47_perm[j69] = fRec47_tmp[vsize + j69];
        }
        for (int j71 = 0; j71 < 4; j71 = j71 + 1) {
            fRec46_perm[j71] = fRec46_tmp[vsize + j71];
        }
        /* Vectorizable loop 17 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec1[i] = fRec8[i] + fRec10[i] + fRec12[i] + fRec14[i] + fRec16[i] + fRec18[i] +
                       fRec20[i] + fRec22[i];
        }
        /* Vectorizable loop 18 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec2[i] = fRec32[i] + fRec34[i] + fRec36[i] + fRec38[i] + fRec40[i] + fRec42[i] +
                       fRec44[i] + fRec46[i];
        }
        /* Recursive loop 19 */
        /* Pre code */
        fYec8_idx = (fYec8_idx + fYec8_idx_save) & 1023;
        for (int j32 = 0; j32 < 4; j32 = j32 + 1) {
            fRec6_tmp[j32] = fRec6_perm[j32];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec8[(i + fYec8_idx) & 1023] = fZec1[i] + 0.5 * fRec6[i - 1];
            fRec6[i]                      = fYec8[(i + fYec8_idx - 556) & 1023];
            fRec7[i]                      = fRec6[i - 1] - fZec1[i];
        }
        /* Post code */
        fYec8_idx_save = vsize;
        for (int j33 = 0; j33 < 4; j33 = j33 + 1) {
            fRec6_perm[j33] = fRec6_tmp[vsize + j33];
        }
        /* Recursive loop 20 */
        /* Pre code */
        fYec20_idx = (fYec20_idx + fYec20_idx_save) & 1023;
        for (int j72 = 0; j72 < 4; j72 = j72 + 1) {
            fRec30_tmp[j72] = fRec30_perm[j72];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec20[(i + fYec20_idx) & 1023] = fZec2[i] + 0.5 * fRec30[i - 1];
            fRec30[i]                       = fYec20[(i + fYec20_idx - 579) & 1023];
            fRec31[i]                       = fRec30[i - 1] - fZec2[i];
        }
        /* Post code */
        fYec20_idx_save = vsize;
        for (int j73 = 0; j73 < 4; j73 = j73 + 1) {
            fRec30_perm[j73] = fRec30_tmp[vsize + j73];
        }
        /* Recursive loop 21 */
        /* Pre code */
        fYec9_idx = (fYec9_idx + fYec9_idx_save) & 511;
        for (int j34 = 0; j34 < 4; j34 = j34 + 1) {
            fRec4_tmp[j34] = fRec4_perm[j34];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec9[(i + fYec9_idx) & 511] = fRec7[i] + 0.5 * fRec4[i - 1];
            fRec4[i]                     = fYec9[(i + fYec9_idx - 441) & 511];
            fRec5[i]                     = fRec4[i - 1] - fRec7[i];
        }
        /* Post code */
        fYec9_idx_save = vsize;
        for (int j35 = 0; j35 < 4; j35 = j35 + 1) {
            fRec4_perm[j35] = fRec4_tmp[vsize + j35];
        }
        /* Recursive loop 22 */
        /* Pre code */
        fYec21_idx = (fYec21_idx + fYec21_idx_save) & 511;
        for (int j74 = 0; j74 < 4; j74 = j74 + 1) {
            fRec28_tmp[j74] = fRec28_perm[j74];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec21[(i + fYec21_idx) & 511] = fRec31[i] + 0.5 * fRec28[i - 1];
            fRec28[i]                      = fYec21[(i + fYec21_idx - 464) & 511];
            fRec29[i]                      = fRec28[i - 1] - fRec31[i];
        }
        /* Post code */
        fYec21_idx_save = vsize;
        for (int j75 = 0; j75 < 4; j75 = j75 + 1) {
            fRec28_perm[j75] = fRec28_tmp[vsize + j75];
        }
        /* Recursive loop 23 */
        /* Pre code */
        fYec10_idx = (fYec10_idx + fYec10_idx_save) & 511;
        for (int j36 = 0; j36 < 4; j36 = j36 + 1) {
            fRec2_tmp[j36] = fRec2_perm[j36];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec10[(i + fYec10_idx) & 511] = fRec5[i] + 0.5 * fRec2[i - 1];
            fRec2[i]                       = fYec10[(i + fYec10_idx - 341) & 511];
            fRec3[i]                       = fRec2[i - 1] - fRec5[i];
        }
        /* Post code */
        fYec10_idx_save = vsize;
        for (int j37 = 0; j37 < 4; j37 = j37 + 1) {
            fRec2_perm[j37] = fRec2_tmp[vsize + j37];
        }
        /* Recursive loop 24 */
        /* Pre code */
        fYec22_idx = (fYec22_idx + fYec22_idx_save) & 511;
        for (int j76 = 0; j76 < 4; j76 = j76 + 1) {
            fRec26_tmp[j76] = fRec26_perm[j76];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec22[(i + fYec22_idx) & 511] = fRec29[i] + 0.5 * fRec26[i - 1];
            fRec26[i]                      = fYec22[(i + fYec22_idx - 364) & 511];
            fRec27[i]                      = fRec26[i - 1] - fRec29[i];
        }
        /* Post code */
        fYec22_idx_save = vsize;
        for (int j77 = 0; j77 < 4; j77 = j77 + 1) {
            fRec26_perm[j77] = fRec26_tmp[vsize + j77];
        }
        /* Recursive loop 25 */
        /* Pre code */
        fYec11_idx = (fYec11_idx + fYec11_idx_save) & 511;
        for (int j38 = 0; j38 < 4; j38 = j38 + 1) {
            fRec0_tmp[j38] = fRec0_perm[j38];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec11[(i + fYec11_idx) & 511] = fRec3[i] + 0.5 * fRec0[i - 1];
            fRec0[i]                       = fYec11[(i + fYec11_idx - 225) & 511];
            fRec1[i]                       = fRec0[i - 1] - fRec3[i];
        }
        /* Post code */
        fYec11_idx_save = vsize;
        for (int j39 = 0; j39 < 4; j39 = j39 + 1) {
            fRec0_perm[j39] = fRec0_tmp[vsize + j39];
        }
        /* Recursive loop 26 */
        /* Pre code */
        fYec23_idx = (fYec23_idx + fYec23_idx_save) & 511;
        for (int j78 = 0; j78 < 4; j78 = j78 + 1) {
            fRec24_tmp[j78] = fRec24_perm[j78];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec23[(i + fYec23_idx) & 511] = fRec27[i] + 0.5 * fRec24[i - 1];
            fRec24[i]                      = fYec23[(i + fYec23_idx - 248) & 511];
            fRec25[i]                      = fRec24[i - 1] - fRec27[i];
        }
        /* Post code */
        fYec23_idx_save = vsize;
        for (int j79 = 0; j79 < 4; j79 = j79 + 1) {
            fRec24_perm[j79] = fRec24_tmp[vsize + j79];
        }
        /* Vectorizable loop 27 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            output0[i] = static_cast<FAUSTFLOAT>(fSlow3 * fRec1[i] +
                                                 fSlow4 * static_cast<double>(input0[i]));
        }
        /* Vectorizable loop 28 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            output1[i] = static_cast<FAUSTFLOAT>(fSlow3 * fRec25[i] +
                                                 fSlow4 * static_cast<double>(input1[i]));
        }
    }
}

virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs)
{
    FAUSTFLOAT* output0_ptr = outputs[0];
    FAUSTFLOAT* output1_ptr = outputs[1];
    int         iRec1_tmp[36];
    int*        iRec1  = &iRec1_tmp[4];
    double      fSlow0 = 0.09999999999999998 * static_cast<double>(fHslider0);
    double      fRec3_tmp[36];
    double*     fRec3 = &fRec3_tmp[4];
    double      fZec0[32];
    double      fZec1[32];
    int         iYec0_tmp[36];
    int*        iYec0 = &iYec0_tmp[4];
    double      fRec2_tmp[36];
    double*     fRec2  = &fRec2_tmp[4];
    double      fSlow1 = 0.5 * (1.0 - static_cast<double>(fHslider1));
    double  fSlow2 = 4.656612875245797e-10 * mydsp_faustpower2_f(static_cast<double>(fHslider2));
    double  fZec2[32];
    double  fRec0_tmp[36];
    double* fRec0 = &fRec0_tmp[4];
    int     iYec2_tmp[36];
    int*    iYec2 = &iYec2_tmp[4];
    double  fRec5_tmp[36];
    double* fRec5 = &fRec5_tmp[4];
    double  fRec4_tmp[36];
    double* fRec4 = &fRec4_tmp[4];
    int     iYec4_tmp[36];
    int*    iYec4 = &iYec4_tmp[4];
    double  fRec7_tmp[36];
    double* fRec7 = &fRec7_tmp[4];
    double  fRec6_tmp[36];
    double* fRec6 = &fRec6_tmp[4];
    int     iYec6_tmp[36];
    int*    iYec6 = &iYec6_tmp[4];
    double  fRec9_tmp[36];
    double* fRec9 = &fRec9_tmp[4];
    double  fRec8_tmp[36];
    double* fRec8 = &fRec8_tmp[4];
    int     iYec8_tmp[36];
    int*    iYec8 = &iYec8_tmp[4];
    double  fRec11_tmp[36];
    double* fRec11 = &fRec11_tmp[4];
    double  fRec10_tmp[36];
    double* fRec10 = &fRec10_tmp[4];
    int     iYec10_tmp[36];
    int*    iYec10 = &iYec10_tmp[4];
    double  fRec13_tmp[36];
    double* fRec13 = &fRec13_tmp[4];
    double  fRec12_tmp[36];
    double* fRec12 = &fRec12_tmp[4];
    int     iYec12_tmp[36];
    int*    iYec12 = &iYec12_tmp[4];
    double  fRec15_tmp[36];
    double* fRec15 = &fRec15_tmp[4];
    double  fRec14_tmp[36];
    double* fRec14 = &fRec14_tmp[4];
    int     iYec14_tmp[36];
    int*    iYec14 = &iYec14_tmp[4];
    double  fRec17_tmp[36];
    double* fRec17 = &fRec17_tmp[4];
    double  fRec16_tmp[36];
    double* fRec16 = &fRec16_tmp[4];
    int     iYec16_tmp[36];
    int*    iYec16 = &iYec16_tmp[4];
    double  fRec19_tmp[36];
    double* fRec19 = &fRec19_tmp[4];
    double  fRec18_tmp[36];
    double* fRec18 = &fRec18_tmp[4];
    int     iYec18_tmp[36];
    int*    iYec18 = &iYec18_tmp[4];
    double  fRec21_tmp[36];
    double* fRec21 = &fRec21_tmp[4];
    double  fRec20_tmp[36];
    double* fRec20 = &fRec20_tmp[4];
    int     iYec20_tmp[36];
    int*    iYec20 = &iYec20_tmp[4];
    double  fRec23_tmp[36];
    double* fRec23 = &fRec23_tmp[4];
    double  fRec22_tmp[36];
    double* fRec22 = &fRec22_tmp[4];
    double  fZec3[32];
    int     vindex = 0;
    /* Main loop */
    for (vindex = 0; vindex <= (count - 32); vindex = vindex + 32) {
        FAUSTFLOAT* output0 = &output0_ptr[vindex];
        FAUSTFLOAT* output1 = &output1_ptr[vindex];
        int         vsize   = 32;
        /* Recursive loop 0 */
        /* Pre code */
        for (int j2 = 0; j2 < 4; j2 = j2 + 1) {
            fRec3_tmp[j2] = fRec3_perm[j2];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec3[i] = fSlow0 + 0.9 * fRec3[i - 1];
        }
        /* Post code */
        for (int j3 = 0; j3 < 4; j3 = j3 + 1) {
            fRec3_perm[j3] = fRec3_tmp[vsize + j3];
        }
        /* Vectorizable loop 1 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec0[i] = std::min<double>(fRec3[i], fRec3[i - 1]);
        }
        /* Vectorizable loop 2 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec1[i] = std::max<double>(fRec3[i], fRec3[i - 1]);
        }
        /* Recursive loop 3 */
        /* Pre code */
        for (int j0 = 0; j0 < 4; j0 = j0 + 1) {
            iRec1_tmp[j0] = iRec1_perm[j0];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iRec1[i] = 1103515245 * iRec1[i - 1] + 12345;
        }
        /* Post code */
        for (int j1 = 0; j1 < 4; j1 = j1 + 1) {
            iRec1_perm[j1] = iRec1_tmp[vsize + j1];
        }
        /* Vectorizable loop 4 */
        /* Pre code */
        for (int j34 = 0; j34 < 4; j34 = j34 + 1) {
            iYec10_tmp[j34] = iYec10_perm[j34];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iYec10[i] = (fZec0[i] < 0.5) & (0.5 < fZec1[i]);
        }
        /* Post code */
        for (int j35 = 0; j35 < 4; j35 = j35 + 1) {
            iYec10_perm[j35] = iYec10_tmp[vsize + j35];
        }
        /* Vectorizable loop 5 */
        /* Pre code */
        for (int j4 = 0; j4 < 4; j4 = j4 + 1) {
            iYec0_tmp[j4] = iYec0_perm[j4];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iYec0[i] = (fZec0[i] < 0.045454545454545456) & (0.045454545454545456 < fZec1[i]);
        }
        /* Post code */
        for (int j5 = 0; j5 < 4; j5 = j5 + 1) {
            iYec0_perm[j5] = iYec0_tmp[vsize + j5];
        }
        /* Vectorizable loop 6 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec2[i] = static_cast<double>(iRec1[i]);
        }
        /* Vectorizable loop 7 */
        /* Pre code */
        for (int j10 = 0; j10 < 4; j10 = j10 + 1) {
            iYec2_tmp[j10] = iYec2_perm[j10];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iYec2[i] = (fZec0[i] < 0.13636363636363635) & (0.13636363636363635 < fZec1[i]);
        }
        /* Post code */
        for (int j11 = 0; j11 < 4; j11 = j11 + 1) {
            iYec2_perm[j11] = iYec2_tmp[vsize + j11];
        }
        /* Vectorizable loop 8 */
        /* Pre code */
        for (int j16 = 0; j16 < 4; j16 = j16 + 1) {
            iYec4_tmp[j16] = iYec4_perm[j16];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iYec4[i] = (fZec0[i] < 0.22727272727272727) & (0.22727272727272727 < fZec1[i]);
        }
        /* Post code */
        for (int j17 = 0; j17 < 4; j17 = j17 + 1) {
            iYec4_perm[j17] = iYec4_tmp[vsize + j17];
        }
        /* Vectorizable loop 9 */
        /* Pre code */
        for (int j22 = 0; j22 < 4; j22 = j22 + 1) {
            iYec6_tmp[j22] = iYec6_perm[j22];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iYec6[i] = (fZec0[i] < 0.3181818181818182) & (0.3181818181818182 < fZec1[i]);
        }
        /* Post code */
        for (int j23 = 0; j23 < 4; j23 = j23 + 1) {
            iYec6_perm[j23] = iYec6_tmp[vsize + j23];
        }
        /* Vectorizable loop 10 */
        /* Pre code */
        for (int j28 = 0; j28 < 4; j28 = j28 + 1) {
            iYec8_tmp[j28] = iYec8_perm[j28];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iYec8[i] = (fZec0[i] < 0.4090909090909091) & (0.4090909090909091 < fZec1[i]);
        }
        /* Post code */
        for (int j29 = 0; j29 < 4; j29 = j29 + 1) {
            iYec8_perm[j29] = iYec8_tmp[vsize + j29];
        }
        /* Recursive loop 11 */
        /* Pre code */
        for (int j36 = 0; j36 < 4; j36 = j36 + 1) {
            fRec13_tmp[j36] = fRec13_perm[j36];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec13[i] = fRec13[i - 1] +
                        static_cast<double>(static_cast<double>(iYec10[i] - iYec10[i - 1]) > 0.0) -
                        0.019954648526077097 * static_cast<double>(fRec13[i - 1] > 0.0);
        }
        /* Post code */
        for (int j37 = 0; j37 < 4; j37 = j37 + 1) {
            fRec13_perm[j37] = fRec13_tmp[vsize + j37];
        }
        /* Vectorizable loop 12 */
        /* Pre code */
        for (int j40 = 0; j40 < 4; j40 = j40 + 1) {
            iYec12_tmp[j40] = iYec12_perm[j40];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iYec12[i] = (fZec0[i] < 0.5909090909090909) & (0.5909090909090909 < fZec1[i]);
        }
        /* Post code */
        for (int j41 = 0; j41 < 4; j41 = j41 + 1) {
            iYec12_perm[j41] = iYec12_tmp[vsize + j41];
        }
        /* Vectorizable loop 13 */
        /* Pre code */
        for (int j46 = 0; j46 < 4; j46 = j46 + 1) {
            iYec14_tmp[j46] = iYec14_perm[j46];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iYec14[i] = (fZec0[i] < 0.6818181818181818) & (0.6818181818181818 < fZec1[i]);
        }
        /* Post code */
        for (int j47 = 0; j47 < 4; j47 = j47 + 1) {
            iYec14_perm[j47] = iYec14_tmp[vsize + j47];
        }
        /* Vectorizable loop 14 */
        /* Pre code */
        for (int j52 = 0; j52 < 4; j52 = j52 + 1) {
            iYec16_tmp[j52] = iYec16_perm[j52];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iYec16[i] = (fZec0[i] < 0.7727272727272727) & (0.7727272727272727 < fZec1[i]);
        }
        /* Post code */
        for (int j53 = 0; j53 < 4; j53 = j53 + 1) {
            iYec16_perm[j53] = iYec16_tmp[vsize + j53];
        }
        /* Vectorizable loop 15 */
        /* Pre code */
        for (int j58 = 0; j58 < 4; j58 = j58 + 1) {
            iYec18_tmp[j58] = iYec18_perm[j58];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iYec18[i] = (fZec0[i] < 0.8636363636363636) & (0.8636363636363636 < fZec1[i]);
        }
        /* Post code */
        for (int j59 = 0; j59 < 4; j59 = j59 + 1) {
            iYec18_perm[j59] = iYec18_tmp[vsize + j59];
        }
        /* Vectorizable loop 16 */
        /* Pre code */
        for (int j64 = 0; j64 < 4; j64 = j64 + 1) {
            iYec20_tmp[j64] = iYec20_perm[j64];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iYec20[i] = (fZec0[i] < 0.9545454545454546) & (0.9545454545454546 < fZec1[i]);
        }
        /* Post code */
        for (int j65 = 0; j65 < 4; j65 = j65 + 1) {
            iYec20_perm[j65] = iYec20_tmp[vsize + j65];
        }
        /* Recursive loop 17 */
        /* Pre code */
        for (int j6 = 0; j6 < 4; j6 = j6 + 1) {
            fRec2_tmp[j6] = fRec2_perm[j6];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec2[i] = fRec2[i - 1] +
                       static_cast<double>(static_cast<double>(iYec0[i] - iYec0[i - 1]) > 0.0) -
                       0.009977324263038548 * static_cast<double>(fRec2[i - 1] > 0.0);
        }
        /* Post code */
        for (int j7 = 0; j7 < 4; j7 = j7 + 1) {
            fRec2_perm[j7] = fRec2_tmp[vsize + j7];
        }
        /* Recursive loop 18 */
        /* Pre code */
        for (int j12 = 0; j12 < 4; j12 = j12 + 1) {
            fRec5_tmp[j12] = fRec5_perm[j12];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec5[i] = fRec5[i - 1] +
                       static_cast<double>(static_cast<double>(iYec2[i] - iYec2[i - 1]) > 0.0) -
                       0.011460935968224386 * static_cast<double>(fRec5[i - 1] > 0.0);
        }
        /* Post code */
        for (int j13 = 0; j13 < 4; j13 = j13 + 1) {
            fRec5_perm[j13] = fRec5_tmp[vsize + j13];
        }
        /* Recursive loop 19 */
        /* Pre code */
        for (int j18 = 0; j18 < 4; j18 = j18 + 1) {
            fRec7_tmp[j18] = fRec7_perm[j18];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec7[i] = fRec7[i - 1] +
                       static_cast<double>(static_cast<double>(iYec4[i] - iYec4[i - 1]) > 0.0) -
                       0.013165158293425702 * static_cast<double>(fRec7[i - 1] > 0.0);
        }
        /* Post code */
        for (int j19 = 0; j19 < 4; j19 = j19 + 1) {
            fRec7_perm[j19] = fRec7_tmp[vsize + j19];
        }
        /* Recursive loop 20 */
        /* Pre code */
        for (int j24 = 0; j24 < 4; j24 = j24 + 1) {
            fRec9_tmp[j24] = fRec9_perm[j24];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec9[i] = fRec9[i - 1] +
                       static_cast<double>(static_cast<double>(iYec6[i] - iYec6[i - 1]) > 0.0) -
                       0.015122795674933676 * static_cast<double>(fRec9[i - 1] > 0.0);
        }
        /* Post code */
        for (int j25 = 0; j25 < 4; j25 = j25 + 1) {
            fRec9_perm[j25] = fRec9_tmp[vsize + j25];
        }
        /* Recursive loop 21 */
        /* Pre code */
        for (int j30 = 0; j30 < 4; j30 = j30 + 1) {
            fRec11_tmp[j30] = fRec11_perm[j30];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec11[i] = fRec11[i - 1] +
                        static_cast<double>(static_cast<double>(iYec8[i] - iYec8[i - 1]) > 0.0) -
                        0.01737153051475259 * static_cast<double>(fRec11[i - 1] > 0.0);
        }
        /* Post code */
        for (int j31 = 0; j31 < 4; j31 = j31 + 1) {
            fRec11_perm[j31] = fRec11_tmp[vsize + j31];
        }
        /* Recursive loop 22 */
        /* Pre code */
        fYec11_idx = (fYec11_idx + fYec11_idx_save) & 127;
        for (int j38 = 0; j38 < 4; j38 = j38 + 1) {
            fRec12_tmp[j38] = fRec12_perm[j38];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec11[(i + fYec11_idx) & 127] =
                fSlow1 * (fRec12[i - 1] + fRec12[i - 2]) +
                fSlow2 * fZec2[i] * static_cast<double>(fRec13[i] > 0.0);
            fRec12[i] = fYec11[(i + fYec11_idx - 49) & 127];
        }
        /* Post code */
        fYec11_idx_save = vsize;
        for (int j39 = 0; j39 < 4; j39 = j39 + 1) {
            fRec12_perm[j39] = fRec12_tmp[vsize + j39];
        }
        /* Recursive loop 23 */
        /* Pre code */
        for (int j42 = 0; j42 < 4; j42 = j42 + 1) {
            fRec15_tmp[j42] = fRec15_perm[j42];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec15[i] = fRec15[i - 1] +
                        static_cast<double>(static_cast<double>(iYec12[i] - iYec12[i - 1]) > 0.0) -
                        0.02292187193644877 * static_cast<double>(fRec15[i - 1] > 0.0);
        }
        /* Post code */
        for (int j43 = 0; j43 < 4; j43 = j43 + 1) {
            fRec15_perm[j43] = fRec15_tmp[vsize + j43];
        }
        /* Recursive loop 24 */
        /* Pre code */
        for (int j48 = 0; j48 < 4; j48 = j48 + 1) {
            fRec17_tmp[j48] = fRec17_perm[j48];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec17[i] = fRec17[i - 1] +
                        static_cast<double>(static_cast<double>(iYec14[i] - iYec14[i - 1]) > 0.0) -
                        0.026330316586851404 * static_cast<double>(fRec17[i - 1] > 0.0);
        }
        /* Post code */
        for (int j49 = 0; j49 < 4; j49 = j49 + 1) {
            fRec17_perm[j49] = fRec17_tmp[vsize + j49];
        }
        /* Recursive loop 25 */
        /* Pre code */
        for (int j54 = 0; j54 < 4; j54 = j54 + 1) {
            fRec19_tmp[j54] = fRec19_perm[j54];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec19[i] = fRec19[i - 1] +
                        static_cast<double>(static_cast<double>(iYec16[i] - iYec16[i - 1]) > 0.0) -
                        0.03024559134986736 * static_cast<double>(fRec19[i - 1] > 0.0);
        }
        /* Post code */
        for (int j55 = 0; j55 < 4; j55 = j55 + 1) {
            fRec19_perm[j55] = fRec19_tmp[vsize + j55];
        }
        /* Recursive loop 26 */
        /* Pre code */
        for (int j60 = 0; j60 < 4; j60 = j60 + 1) {
            fRec21_tmp[j60] = fRec21_perm[j60];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec21[i] = fRec21[i - 1] +
                        static_cast<double>(static_cast<double>(iYec18[i] - iYec18[i - 1]) > 0.0) -
                        0.03474306102950518 * static_cast<double>(fRec21[i - 1] > 0.0);
        }
        /* Post code */
        for (int j61 = 0; j61 < 4; j61 = j61 + 1) {
            fRec21_perm[j61] = fRec21_tmp[vsize + j61];
        }
        /* Recursive loop 27 */
        /* Pre code */
        for (int j66 = 0; j66 < 4; j66 = j66 + 1) {
            fRec23_tmp[j66] = fRec23_perm[j66];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec23[i] = fRec23[i - 1] +
                        static_cast<double>(static_cast<double>(iYec20[i] - iYec20[i - 1]) > 0.0) -
                        0.039909297052154194 * static_cast<double>(fRec23[i - 1] > 0.0);
        }
        /* Post code */
        for (int j67 = 0; j67 < 4; j67 = j67 + 1) {
            fRec23_perm[j67] = fRec23_tmp[vsize + j67];
        }
        /* Recursive loop 28 */
        /* Pre code */
        fYec1_idx = (fYec1_idx + fYec1_idx_save) & 255;
        for (int j8 = 0; j8 < 4; j8 = j8 + 1) {
            fRec0_tmp[j8] = fRec0_perm[j8];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec1[(i + fYec1_idx) & 255] = fSlow1 * (fRec0[i - 1] + fRec0[i - 2]) +
                                           fSlow2 * fZec2[i] * static_cast<double>(fRec2[i] > 0.0);
            fRec0[i]                     = fYec1[(i + fYec1_idx - 99) & 255];
        }
        /* Post code */
        fYec1_idx_save = vsize;
        for (int j9 = 0; j9 < 4; j9 = j9 + 1) {
            fRec0_perm[j9] = fRec0_tmp[vsize + j9];
        }
        /* Recursive loop 29 */
        /* Pre code */
        fYec3_idx = (fYec3_idx + fYec3_idx_save) & 127;
        for (int j14 = 0; j14 < 4; j14 = j14 + 1) {
            fRec4_tmp[j14] = fRec4_perm[j14];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec3[(i + fYec3_idx) & 127] = fSlow1 * (fRec4[i - 1] + fRec4[i - 2]) +
                                           fSlow2 * fZec2[i] * static_cast<double>(fRec5[i] > 0.0);
            fRec4[i]                     = fYec3[(i + fYec3_idx - 86) & 127];
        }
        /* Post code */
        fYec3_idx_save = vsize;
        for (int j15 = 0; j15 < 4; j15 = j15 + 1) {
            fRec4_perm[j15] = fRec4_tmp[vsize + j15];
        }
        /* Recursive loop 30 */
        /* Pre code */
        fYec5_idx = (fYec5_idx + fYec5_idx_save) & 127;
        for (int j20 = 0; j20 < 4; j20 = j20 + 1) {
            fRec6_tmp[j20] = fRec6_perm[j20];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec5[(i + fYec5_idx) & 127] = fSlow1 * (fRec6[i - 1] + fRec6[i - 2]) +
                                           fSlow2 * fZec2[i] * static_cast<double>(fRec7[i] > 0.0);
            fRec6[i]                     = fYec5[(i + fYec5_idx - 74) & 127];
        }
        /* Post code */
        fYec5_idx_save = vsize;
        for (int j21 = 0; j21 < 4; j21 = j21 + 1) {
            fRec6_perm[j21] = fRec6_tmp[vsize + j21];
        }
        /* Recursive loop 31 */
        /* Pre code */
        fYec7_idx = (fYec7_idx + fYec7_idx_save) & 127;
        for (int j26 = 0; j26 < 4; j26 = j26 + 1) {
            fRec8_tmp[j26] = fRec8_perm[j26];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec7[(i + fYec7_idx) & 127] = fSlow1 * (fRec8[i - 1] + fRec8[i - 2]) +
                                           fSlow2 * fZec2[i] * static_cast<double>(fRec9[i] > 0.0);
            fRec8[i]                     = fYec7[(i + fYec7_idx - 65) & 127];
        }
        /* Post code */
        fYec7_idx_save = vsize;
        for (int j27 = 0; j27 < 4; j27 = j27 + 1) {
            fRec8_perm[j27] = fRec8_tmp[vsize + j27];
        }
        /* Recursive loop 32 */
        /* Pre code */
        fYec9_idx = (fYec9_idx + fYec9_idx_save) & 127;
        for (int j32 = 0; j32 < 4; j32 = j32 + 1) {
            fRec10_tmp[j32] = fRec10_perm[j32];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec9[(i + fYec9_idx) & 127] = fSlow1 * (fRec10[i - 1] + fRec10[i - 2]) +
                                           fSlow2 * fZec2[i] * static_cast<double>(fRec11[i] > 0.0);
            fRec10[i]                    = fYec9[(i + fYec9_idx - 56) & 127];
        }
        /* Post code */
        fYec9_idx_save = vsize;
        for (int j33 = 0; j33 < 4; j33 = j33 + 1) {
            fRec10_perm[j33] = fRec10_tmp[vsize + j33];
        }
        /* Recursive loop 33 */
        /* Pre code */
        fYec13_idx = (fYec13_idx + fYec13_idx_save) & 127;
        for (int j44 = 0; j44 < 4; j44 = j44 + 1) {
            fRec14_tmp[j44] = fRec14_perm[j44];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec13[(i + fYec13_idx) & 127] =
                fSlow1 * (fRec14[i - 1] + fRec14[i - 2]) +
                fSlow2 * fZec2[i] * static_cast<double>(fRec15[i] > 0.0);
            fRec14[i] = fYec13[(i + fYec13_idx - 42) & 127];
        }
        /* Post code */
        fYec13_idx_save = vsize;
        for (int j45 = 0; j45 < 4; j45 = j45 + 1) {
            fRec14_perm[j45] = fRec14_tmp[vsize + j45];
        }
        /* Recursive loop 34 */
        /* Pre code */
        fYec15_idx = (fYec15_idx + fYec15_idx_save) & 127;
        for (int j50 = 0; j50 < 4; j50 = j50 + 1) {
            fRec16_tmp[j50] = fRec16_perm[j50];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec15[(i + fYec15_idx) & 127] =
                fSlow1 * (fRec16[i - 1] + fRec16[i - 2]) +
                fSlow2 * fZec2[i] * static_cast<double>(fRec17[i] > 0.0);
            fRec16[i] = fYec15[(i + fYec15_idx - 36) & 127];
        }
        /* Post code */
        fYec15_idx_save = vsize;
        for (int j51 = 0; j51 < 4; j51 = j51 + 1) {
            fRec16_perm[j51] = fRec16_tmp[vsize + j51];
        }
        /* Recursive loop 35 */
        /* Pre code */
        fYec17_idx = (fYec17_idx + fYec17_idx_save) & 63;
        for (int j56 = 0; j56 < 4; j56 = j56 + 1) {
            fRec18_tmp[j56] = fRec18_perm[j56];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec17[(i + fYec17_idx) & 63] =
                fSlow1 * (fRec18[i - 1] + fRec18[i - 2]) +
                fSlow2 * fZec2[i] * static_cast<double>(fRec19[i] > 0.0);
            fRec18[i] = fYec17[(i + fYec17_idx - 32) & 63];
        }
        /* Post code */
        fYec17_idx_save = vsize;
        for (int j57 = 0; j57 < 4; j57 = j57 + 1) {
            fRec18_perm[j57] = fRec18_tmp[vsize + j57];
        }
        /* Recursive loop 36 */
        /* Pre code */
        fYec19_idx = (fYec19_idx + fYec19_idx_save) & 63;
        for (int j62 = 0; j62 < 4; j62 = j62 + 1) {
            fRec20_tmp[j62] = fRec20_perm[j62];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec19[(i + fYec19_idx) & 63] =
                fSlow1 * (fRec20[i - 1] + fRec20[i - 2]) +
                fSlow2 * fZec2[i] * static_cast<double>(fRec21[i] > 0.0);
            fRec20[i] = fYec19[(i + fYec19_idx - 27) & 63];
        }
        /* Post code */
        fYec19_idx_save = vsize;
        for (int j63 = 0; j63 < 4; j63 = j63 + 1) {
            fRec20_perm[j63] = fRec20_tmp[vsize + j63];
        }
        /* Recursive loop 37 */
        /* Pre code */
        fYec21_idx = (fYec21_idx + fYec21_idx_save) & 63;
        for (int j68 = 0; j68 < 4; j68 = j68 + 1) {
            fRec22_tmp[j68] = fRec22_perm[j68];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec21[(i + fYec21_idx) & 63] =
                fSlow1 * (fRec22[i - 1] + fRec22[i - 2]) +
                fSlow2 * fZec2[i] * static_cast<double>(fRec23[i] > 0.0);
            fRec22[i] = fYec21[(i + fYec21_idx - 24) & 63];
        }
        /* Post code */
        fYec21_idx_save = vsize;
        for (int j69 = 0; j69 < 4; j69 = j69 + 1) {
            fRec22_perm[j69] = fRec22_tmp[vsize + j69];
        }
        /* Vectorizable loop 38 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec3[i] = 0.7071067811865476 * fRec12[i];
        }
        /* Vectorizable loop 39 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            output0[i] = static_cast<FAUSTFLOAT>(
                0.9770084209183945 * fRec0[i] + 0.9293203772845852 * fRec4[i] +
                0.8790490729915326 * fRec6[i] + 0.8257228238447705 * fRec8[i] +
                0.7687061147858073 * fRec10[i] + fZec3[i] + 0.6396021490668313 * fRec14[i] +
                0.5640760748177662 * fRec16[i] + 0.4767312946227962 * fRec18[i] +
                0.3692744729379982 * fRec20[i] + 0.21320071635561033 * fRec22[i]);
        }
        /* Vectorizable loop 40 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            output1[i] = static_cast<FAUSTFLOAT>(
                fZec3[i] + 0.21320071635561044 * fRec0[i] + 0.3692744729379982 * fRec4[i] +
                0.4767312946227962 * fRec6[i] + 0.5640760748177662 * fRec8[i] +
                0.6396021490668313 * fRec10[i] + 0.7687061147858074 * fRec14[i] +
                0.8257228238447705 * fRec16[i] + 0.8790490729915326 * fRec18[i] +
                0.9293203772845852 * fRec20[i] + 0.9770084209183945 * fRec22[i]);
        }
    }
    /* Remaining frames */
    if (vindex < count) {
        FAUSTFLOAT* output0 = &output0_ptr[vindex];
        FAUSTFLOAT* output1 = &output1_ptr[vindex];
        int         vsize   = count - vindex;
        /* Recursive loop 0 */
        /* Pre code */
        for (int j2 = 0; j2 < 4; j2 = j2 + 1) {
            fRec3_tmp[j2] = fRec3_perm[j2];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec3[i] = fSlow0 + 0.9 * fRec3[i - 1];
        }
        /* Post code */
        for (int j3 = 0; j3 < 4; j3 = j3 + 1) {
            fRec3_perm[j3] = fRec3_tmp[vsize + j3];
        }
        /* Vectorizable loop 1 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec0[i] = std::min<double>(fRec3[i], fRec3[i - 1]);
        }
        /* Vectorizable loop 2 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec1[i] = std::max<double>(fRec3[i], fRec3[i - 1]);
        }
        /* Recursive loop 3 */
        /* Pre code */
        for (int j0 = 0; j0 < 4; j0 = j0 + 1) {
            iRec1_tmp[j0] = iRec1_perm[j0];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iRec1[i] = 1103515245 * iRec1[i - 1] + 12345;
        }
        /* Post code */
        for (int j1 = 0; j1 < 4; j1 = j1 + 1) {
            iRec1_perm[j1] = iRec1_tmp[vsize + j1];
        }
        /* Vectorizable loop 4 */
        /* Pre code */
        for (int j34 = 0; j34 < 4; j34 = j34 + 1) {
            iYec10_tmp[j34] = iYec10_perm[j34];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iYec10[i] = (fZec0[i] < 0.5) & (0.5 < fZec1[i]);
        }
        /* Post code */
        for (int j35 = 0; j35 < 4; j35 = j35 + 1) {
            iYec10_perm[j35] = iYec10_tmp[vsize + j35];
        }
        /* Vectorizable loop 5 */
        /* Pre code */
        for (int j4 = 0; j4 < 4; j4 = j4 + 1) {
            iYec0_tmp[j4] = iYec0_perm[j4];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iYec0[i] = (fZec0[i] < 0.045454545454545456) & (0.045454545454545456 < fZec1[i]);
        }
        /* Post code */
        for (int j5 = 0; j5 < 4; j5 = j5 + 1) {
            iYec0_perm[j5] = iYec0_tmp[vsize + j5];
        }
        /* Vectorizable loop 6 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec2[i] = static_cast<double>(iRec1[i]);
        }
        /* Vectorizable loop 7 */
        /* Pre code */
        for (int j10 = 0; j10 < 4; j10 = j10 + 1) {
            iYec2_tmp[j10] = iYec2_perm[j10];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iYec2[i] = (fZec0[i] < 0.13636363636363635) & (0.13636363636363635 < fZec1[i]);
        }
        /* Post code */
        for (int j11 = 0; j11 < 4; j11 = j11 + 1) {
            iYec2_perm[j11] = iYec2_tmp[vsize + j11];
        }
        /* Vectorizable loop 8 */
        /* Pre code */
        for (int j16 = 0; j16 < 4; j16 = j16 + 1) {
            iYec4_tmp[j16] = iYec4_perm[j16];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iYec4[i] = (fZec0[i] < 0.22727272727272727) & (0.22727272727272727 < fZec1[i]);
        }
        /* Post code */
        for (int j17 = 0; j17 < 4; j17 = j17 + 1) {
            iYec4_perm[j17] = iYec4_tmp[vsize + j17];
        }
        /* Vectorizable loop 9 */
        /* Pre code */
        for (int j22 = 0; j22 < 4; j22 = j22 + 1) {
            iYec6_tmp[j22] = iYec6_perm[j22];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iYec6[i] = (fZec0[i] < 0.3181818181818182) & (0.3181818181818182 < fZec1[i]);
        }
        /* Post code */
        for (int j23 = 0; j23 < 4; j23 = j23 + 1) {
            iYec6_perm[j23] = iYec6_tmp[vsize + j23];
        }
        /* Vectorizable loop 10 */
        /* Pre code */
        for (int j28 = 0; j28 < 4; j28 = j28 + 1) {
            iYec8_tmp[j28] = iYec8_perm[j28];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iYec8[i] = (fZec0[i] < 0.4090909090909091) & (0.4090909090909091 < fZec1[i]);
        }
        /* Post code */
        for (int j29 = 0; j29 < 4; j29 = j29 + 1) {
            iYec8_perm[j29] = iYec8_tmp[vsize + j29];
        }
        /* Recursive loop 11 */
        /* Pre code */
        for (int j36 = 0; j36 < 4; j36 = j36 + 1) {
            fRec13_tmp[j36] = fRec13_perm[j36];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec13[i] = fRec13[i - 1] +
                        static_cast<double>(static_cast<double>(iYec10[i] - iYec10[i - 1]) > 0.0) -
                        0.019954648526077097 * static_cast<double>(fRec13[i - 1] > 0.0);
        }
        /* Post code */
        for (int j37 = 0; j37 < 4; j37 = j37 + 1) {
            fRec13_perm[j37] = fRec13_tmp[vsize + j37];
        }
        /* Vectorizable loop 12 */
        /* Pre code */
        for (int j40 = 0; j40 < 4; j40 = j40 + 1) {
            iYec12_tmp[j40] = iYec12_perm[j40];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iYec12[i] = (fZec0[i] < 0.5909090909090909) & (0.5909090909090909 < fZec1[i]);
        }
        /* Post code */
        for (int j41 = 0; j41 < 4; j41 = j41 + 1) {
            iYec12_perm[j41] = iYec12_tmp[vsize + j41];
        }
        /* Vectorizable loop 13 */
        /* Pre code */
        for (int j46 = 0; j46 < 4; j46 = j46 + 1) {
            iYec14_tmp[j46] = iYec14_perm[j46];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iYec14[i] = (fZec0[i] < 0.6818181818181818) & (0.6818181818181818 < fZec1[i]);
        }
        /* Post code */
        for (int j47 = 0; j47 < 4; j47 = j47 + 1) {
            iYec14_perm[j47] = iYec14_tmp[vsize + j47];
        }
        /* Vectorizable loop 14 */
        /* Pre code */
        for (int j52 = 0; j52 < 4; j52 = j52 + 1) {
            iYec16_tmp[j52] = iYec16_perm[j52];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iYec16[i] = (fZec0[i] < 0.7727272727272727) & (0.7727272727272727 < fZec1[i]);
        }
        /* Post code */
        for (int j53 = 0; j53 < 4; j53 = j53 + 1) {
            iYec16_perm[j53] = iYec16_tmp[vsize + j53];
        }
        /* Vectorizable loop 15 */
        /* Pre code */
        for (int j58 = 0; j58 < 4; j58 = j58 + 1) {
            iYec18_tmp[j58] = iYec18_perm[j58];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iYec18[i] = (fZec0[i] < 0.8636363636363636) & (0.8636363636363636 < fZec1[i]);
        }
        /* Post code */
        for (int j59 = 0; j59 < 4; j59 = j59 + 1) {
            iYec18_perm[j59] = iYec18_tmp[vsize + j59];
        }
        /* Vectorizable loop 16 */
        /* Pre code */
        for (int j64 = 0; j64 < 4; j64 = j64 + 1) {
            iYec20_tmp[j64] = iYec20_perm[j64];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iYec20[i] = (fZec0[i] < 0.9545454545454546) & (0.9545454545454546 < fZec1[i]);
        }
        /* Post code */
        for (int j65 = 0; j65 < 4; j65 = j65 + 1) {
            iYec20_perm[j65] = iYec20_tmp[vsize + j65];
        }
        /* Recursive loop 17 */
        /* Pre code */
        for (int j6 = 0; j6 < 4; j6 = j6 + 1) {
            fRec2_tmp[j6] = fRec2_perm[j6];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec2[i] = fRec2[i - 1] +
                       static_cast<double>(static_cast<double>(iYec0[i] - iYec0[i - 1]) > 0.0) -
                       0.009977324263038548 * static_cast<double>(fRec2[i - 1] > 0.0);
        }
        /* Post code */
        for (int j7 = 0; j7 < 4; j7 = j7 + 1) {
            fRec2_perm[j7] = fRec2_tmp[vsize + j7];
        }
        /* Recursive loop 18 */
        /* Pre code */
        for (int j12 = 0; j12 < 4; j12 = j12 + 1) {
            fRec5_tmp[j12] = fRec5_perm[j12];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec5[i] = fRec5[i - 1] +
                       static_cast<double>(static_cast<double>(iYec2[i] - iYec2[i - 1]) > 0.0) -
                       0.011460935968224386 * static_cast<double>(fRec5[i - 1] > 0.0);
        }
        /* Post code */
        for (int j13 = 0; j13 < 4; j13 = j13 + 1) {
            fRec5_perm[j13] = fRec5_tmp[vsize + j13];
        }
        /* Recursive loop 19 */
        /* Pre code */
        for (int j18 = 0; j18 < 4; j18 = j18 + 1) {
            fRec7_tmp[j18] = fRec7_perm[j18];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec7[i] = fRec7[i - 1] +
                       static_cast<double>(static_cast<double>(iYec4[i] - iYec4[i - 1]) > 0.0) -
                       0.013165158293425702 * static_cast<double>(fRec7[i - 1] > 0.0);
        }
        /* Post code */
        for (int j19 = 0; j19 < 4; j19 = j19 + 1) {
            fRec7_perm[j19] = fRec7_tmp[vsize + j19];
        }
        /* Recursive loop 20 */
        /* Pre code */
        for (int j24 = 0; j24 < 4; j24 = j24 + 1) {
            fRec9_tmp[j24] = fRec9_perm[j24];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec9[i] = fRec9[i - 1] +
                       static_cast<double>(static_cast<double>(iYec6[i] - iYec6[i - 1]) > 0.0) -
                       0.015122795674933676 * static_cast<double>(fRec9[i - 1] > 0.0);
        }
        /* Post code */
        for (int j25 = 0; j25 < 4; j25 = j25 + 1) {
            fRec9_perm[j25] = fRec9_tmp[vsize + j25];
        }
        /* Recursive loop 21 */
        /* Pre code */
        for (int j30 = 0; j30 < 4; j30 = j30 + 1) {
            fRec11_tmp[j30] = fRec11_perm[j30];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec11[i] = fRec11[i - 1] +
                        static_cast<double>(static_cast<double>(iYec8[i] - iYec8[i - 1]) > 0.0) -
                        0.01737153051475259 * static_cast<double>(fRec11[i - 1] > 0.0);
        }
        /* Post code */
        for (int j31 = 0; j31 < 4; j31 = j31 + 1) {
            fRec11_perm[j31] = fRec11_tmp[vsize + j31];
        }
        /* Recursive loop 22 */
        /* Pre code */
        fYec11_idx = (fYec11_idx + fYec11_idx_save) & 127;
        for (int j38 = 0; j38 < 4; j38 = j38 + 1) {
            fRec12_tmp[j38] = fRec12_perm[j38];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec11[(i + fYec11_idx) & 127] =
                fSlow1 * (fRec12[i - 1] + fRec12[i - 2]) +
                fSlow2 * fZec2[i] * static_cast<double>(fRec13[i] > 0.0);
            fRec12[i] = fYec11[(i + fYec11_idx - 49) & 127];
        }
        /* Post code */
        fYec11_idx_save = vsize;
        for (int j39 = 0; j39 < 4; j39 = j39 + 1) {
            fRec12_perm[j39] = fRec12_tmp[vsize + j39];
        }
        /* Recursive loop 23 */
        /* Pre code */
        for (int j42 = 0; j42 < 4; j42 = j42 + 1) {
            fRec15_tmp[j42] = fRec15_perm[j42];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec15[i] = fRec15[i - 1] +
                        static_cast<double>(static_cast<double>(iYec12[i] - iYec12[i - 1]) > 0.0) -
                        0.02292187193644877 * static_cast<double>(fRec15[i - 1] > 0.0);
        }
        /* Post code */
        for (int j43 = 0; j43 < 4; j43 = j43 + 1) {
            fRec15_perm[j43] = fRec15_tmp[vsize + j43];
        }
        /* Recursive loop 24 */
        /* Pre code */
        for (int j48 = 0; j48 < 4; j48 = j48 + 1) {
            fRec17_tmp[j48] = fRec17_perm[j48];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec17[i] = fRec17[i - 1] +
                        static_cast<double>(static_cast<double>(iYec14[i] - iYec14[i - 1]) > 0.0) -
                        0.026330316586851404 * static_cast<double>(fRec17[i - 1] > 0.0);
        }
        /* Post code */
        for (int j49 = 0; j49 < 4; j49 = j49 + 1) {
            fRec17_perm[j49] = fRec17_tmp[vsize + j49];
        }
        /* Recursive loop 25 */
        /* Pre code */
        for (int j54 = 0; j54 < 4; j54 = j54 + 1) {
            fRec19_tmp[j54] = fRec19_perm[j54];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec19[i] = fRec19[i - 1] +
                        static_cast<double>(static_cast<double>(iYec16[i] - iYec16[i - 1]) > 0.0) -
                        0.03024559134986736 * static_cast<double>(fRec19[i - 1] > 0.0);
        }
        /* Post code */
        for (int j55 = 0; j55 < 4; j55 = j55 + 1) {
            fRec19_perm[j55] = fRec19_tmp[vsize + j55];
        }
        /* Recursive loop 26 */
        /* Pre code */
        for (int j60 = 0; j60 < 4; j60 = j60 + 1) {
            fRec21_tmp[j60] = fRec21_perm[j60];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec21[i] = fRec21[i - 1] +
                        static_cast<double>(static_cast<double>(iYec18[i] - iYec18[i - 1]) > 0.0) -
                        0.03474306102950518 * static_cast<double>(fRec21[i - 1] > 0.0);
        }
        /* Post code */
        for (int j61 = 0; j61 < 4; j61 = j61 + 1) {
            fRec21_perm[j61] = fRec21_tmp[vsize + j61];
        }
        /* Recursive loop 27 */
        /* Pre code */
        for (int j66 = 0; j66 < 4; j66 = j66 + 1) {
            fRec23_tmp[j66] = fRec23_perm[j66];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec23[i] = fRec23[i - 1] +
                        static_cast<double>(static_cast<double>(iYec20[i] - iYec20[i - 1]) > 0.0) -
                        0.039909297052154194 * static_cast<double>(fRec23[i - 1] > 0.0);
        }
        /* Post code */
        for (int j67 = 0; j67 < 4; j67 = j67 + 1) {
            fRec23_perm[j67] = fRec23_tmp[vsize + j67];
        }
        /* Recursive loop 28 */
        /* Pre code */
        fYec1_idx = (fYec1_idx + fYec1_idx_save) & 255;
        for (int j8 = 0; j8 < 4; j8 = j8 + 1) {
            fRec0_tmp[j8] = fRec0_perm[j8];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec1[(i + fYec1_idx) & 255] = fSlow1 * (fRec0[i - 1] + fRec0[i - 2]) +
                                           fSlow2 * fZec2[i] * static_cast<double>(fRec2[i] > 0.0);
            fRec0[i]                     = fYec1[(i + fYec1_idx - 99) & 255];
        }
        /* Post code */
        fYec1_idx_save = vsize;
        for (int j9 = 0; j9 < 4; j9 = j9 + 1) {
            fRec0_perm[j9] = fRec0_tmp[vsize + j9];
        }
        /* Recursive loop 29 */
        /* Pre code */
        fYec3_idx = (fYec3_idx + fYec3_idx_save) & 127;
        for (int j14 = 0; j14 < 4; j14 = j14 + 1) {
            fRec4_tmp[j14] = fRec4_perm[j14];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec3[(i + fYec3_idx) & 127] = fSlow1 * (fRec4[i - 1] + fRec4[i - 2]) +
                                           fSlow2 * fZec2[i] * static_cast<double>(fRec5[i] > 0.0);
            fRec4[i]                     = fYec3[(i + fYec3_idx - 86) & 127];
        }
        /* Post code */
        fYec3_idx_save = vsize;
        for (int j15 = 0; j15 < 4; j15 = j15 + 1) {
            fRec4_perm[j15] = fRec4_tmp[vsize + j15];
        }
        /* Recursive loop 30 */
        /* Pre code */
        fYec5_idx = (fYec5_idx + fYec5_idx_save) & 127;
        for (int j20 = 0; j20 < 4; j20 = j20 + 1) {
            fRec6_tmp[j20] = fRec6_perm[j20];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec5[(i + fYec5_idx) & 127] = fSlow1 * (fRec6[i - 1] + fRec6[i - 2]) +
                                           fSlow2 * fZec2[i] * static_cast<double>(fRec7[i] > 0.0);
            fRec6[i]                     = fYec5[(i + fYec5_idx - 74) & 127];
        }
        /* Post code */
        fYec5_idx_save = vsize;
        for (int j21 = 0; j21 < 4; j21 = j21 + 1) {
            fRec6_perm[j21] = fRec6_tmp[vsize + j21];
        }
        /* Recursive loop 31 */
        /* Pre code */
        fYec7_idx = (fYec7_idx + fYec7_idx_save) & 127;
        for (int j26 = 0; j26 < 4; j26 = j26 + 1) {
            fRec8_tmp[j26] = fRec8_perm[j26];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec7[(i + fYec7_idx) & 127] = fSlow1 * (fRec8[i - 1] + fRec8[i - 2]) +
                                           fSlow2 * fZec2[i] * static_cast<double>(fRec9[i] > 0.0);
            fRec8[i]                     = fYec7[(i + fYec7_idx - 65) & 127];
        }
        /* Post code */
        fYec7_idx_save = vsize;
        for (int j27 = 0; j27 < 4; j27 = j27 + 1) {
            fRec8_perm[j27] = fRec8_tmp[vsize + j27];
        }
        /* Recursive loop 32 */
        /* Pre code */
        fYec9_idx = (fYec9_idx + fYec9_idx_save) & 127;
        for (int j32 = 0; j32 < 4; j32 = j32 + 1) {
            fRec10_tmp[j32] = fRec10_perm[j32];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec9[(i + fYec9_idx) & 127] = fSlow1 * (fRec10[i - 1] + fRec10[i - 2]) +
                                           fSlow2 * fZec2[i] * static_cast<double>(fRec11[i] > 0.0);
            fRec10[i]                    = fYec9[(i + fYec9_idx - 56) & 127];
        }
        /* Post code */
        fYec9_idx_save = vsize;
        for (int j33 = 0; j33 < 4; j33 = j33 + 1) {
            fRec10_perm[j33] = fRec10_tmp[vsize + j33];
        }
        /* Recursive loop 33 */
        /* Pre code */
        fYec13_idx = (fYec13_idx + fYec13_idx_save) & 127;
        for (int j44 = 0; j44 < 4; j44 = j44 + 1) {
            fRec14_tmp[j44] = fRec14_perm[j44];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec13[(i + fYec13_idx) & 127] =
                fSlow1 * (fRec14[i - 1] + fRec14[i - 2]) +
                fSlow2 * fZec2[i] * static_cast<double>(fRec15[i] > 0.0);
            fRec14[i] = fYec13[(i + fYec13_idx - 42) & 127];
        }
        /* Post code */
        fYec13_idx_save = vsize;
        for (int j45 = 0; j45 < 4; j45 = j45 + 1) {
            fRec14_perm[j45] = fRec14_tmp[vsize + j45];
        }
        /* Recursive loop 34 */
        /* Pre code */
        fYec15_idx = (fYec15_idx + fYec15_idx_save) & 127;
        for (int j50 = 0; j50 < 4; j50 = j50 + 1) {
            fRec16_tmp[j50] = fRec16_perm[j50];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec15[(i + fYec15_idx) & 127] =
                fSlow1 * (fRec16[i - 1] + fRec16[i - 2]) +
                fSlow2 * fZec2[i] * static_cast<double>(fRec17[i] > 0.0);
            fRec16[i] = fYec15[(i + fYec15_idx - 36) & 127];
        }
        /* Post code */
        fYec15_idx_save = vsize;
        for (int j51 = 0; j51 < 4; j51 = j51 + 1) {
            fRec16_perm[j51] = fRec16_tmp[vsize + j51];
        }
        /* Recursive loop 35 */
        /* Pre code */
        fYec17_idx = (fYec17_idx + fYec17_idx_save) & 63;
        for (int j56 = 0; j56 < 4; j56 = j56 + 1) {
            fRec18_tmp[j56] = fRec18_perm[j56];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec17[(i + fYec17_idx) & 63] =
                fSlow1 * (fRec18[i - 1] + fRec18[i - 2]) +
                fSlow2 * fZec2[i] * static_cast<double>(fRec19[i] > 0.0);
            fRec18[i] = fYec17[(i + fYec17_idx - 32) & 63];
        }
        /* Post code */
        fYec17_idx_save = vsize;
        for (int j57 = 0; j57 < 4; j57 = j57 + 1) {
            fRec18_perm[j57] = fRec18_tmp[vsize + j57];
        }
        /* Recursive loop 36 */
        /* Pre code */
        fYec19_idx = (fYec19_idx + fYec19_idx_save) & 63;
        for (int j62 = 0; j62 < 4; j62 = j62 + 1) {
            fRec20_tmp[j62] = fRec20_perm[j62];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec19[(i + fYec19_idx) & 63] =
                fSlow1 * (fRec20[i - 1] + fRec20[i - 2]) +
                fSlow2 * fZec2[i] * static_cast<double>(fRec21[i] > 0.0);
            fRec20[i] = fYec19[(i + fYec19_idx - 27) & 63];
        }
        /* Post code */
        fYec19_idx_save = vsize;
        for (int j63 = 0; j63 < 4; j63 = j63 + 1) {
            fRec20_perm[j63] = fRec20_tmp[vsize + j63];
        }
        /* Recursive loop 37 */
        /* Pre code */
        fYec21_idx = (fYec21_idx + fYec21_idx_save) & 63;
        for (int j68 = 0; j68 < 4; j68 = j68 + 1) {
            fRec22_tmp[j68] = fRec22_perm[j68];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec21[(i + fYec21_idx) & 63] =
                fSlow1 * (fRec22[i - 1] + fRec22[i - 2]) +
                fSlow2 * fZec2[i] * static_cast<double>(fRec23[i] > 0.0);
            fRec22[i] = fYec21[(i + fYec21_idx - 24) & 63];
        }
        /* Post code */
        fYec21_idx_save = vsize;
        for (int j69 = 0; j69 < 4; j69 = j69 + 1) {
            fRec22_perm[j69] = fRec22_tmp[vsize + j69];
        }
        /* Vectorizable loop 38 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec3[i] = 0.7071067811865476 * fRec12[i];
        }
        /* Vectorizable loop 39 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            output0[i] = static_cast<FAUSTFLOAT>(
                0.9770084209183945 * fRec0[i] + 0.9293203772845852 * fRec4[i] +
                0.8790490729915326 * fRec6[i] + 0.8257228238447705 * fRec8[i] +
                0.7687061147858073 * fRec10[i] + fZec3[i] + 0.6396021490668313 * fRec14[i] +
                0.5640760748177662 * fRec16[i] + 0.4767312946227962 * fRec18[i] +
                0.3692744729379982 * fRec20[i] + 0.21320071635561033 * fRec22[i]);
        }
        /* Vectorizable loop 40 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            output1[i] = static_cast<FAUSTFLOAT>(
                fZec3[i] + 0.21320071635561044 * fRec0[i] + 0.3692744729379982 * fRec4[i] +
                0.4767312946227962 * fRec6[i] + 0.5640760748177662 * fRec8[i] +
                0.6396021490668313 * fRec10[i] + 0.7687061147858074 * fRec14[i] +
                0.8257228238447705 * fRec16[i] + 0.8790490729915326 * fRec18[i] +
                0.9293203772845852 * fRec20[i] + 0.9770084209183945 * fRec22[i]);
        }
    }
}

virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs)
{
    FAUSTFLOAT* output0_ptr = outputs[0];
    int         iRec1_tmp[36];
    int*        iRec1  = &iRec1_tmp[4];
    double      fSlow0 = static_cast<double>(fButton0);
    double      fVec0_tmp[36];
    double*     fVec0  = &fVec0_tmp[4];
    double      fSlow1 = 1.0 / static_cast<double>(fHslider0);
    double      fRec2_tmp[36];
    double*     fRec2  = &fRec2_tmp[4];
    double      fSlow2 = 0.5 * (1.0 - static_cast<double>(fHslider1));
    double      fSlow3 = 4.656612875245797e-10 * static_cast<double>(fHslider2);
    int         iSlow4 = static_cast<int>(static_cast<double>(fHslider3) + -1.5) & 4095;
    double      fRec0_tmp[36];
    double*     fRec0  = &fRec0_tmp[4];
    int         vindex = 0;
    /* Main loop */
    for (vindex = 0; vindex <= (count - 32); vindex = vindex + 32) {
        FAUSTFLOAT* output0 = &output0_ptr[vindex];
        int         vsize   = 32;
        /* Vectorizable loop 0 */
        /* Pre code */
        for (int j2 = 0; j2 < 4; j2 = j2 + 1) {
            fVec0_tmp[j2] = fVec0_perm[j2];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fVec0[i] = fSlow0;
        }
        /* Post code */
        for (int j3 = 0; j3 < 4; j3 = j3 + 1) {
            fVec0_perm[j3] = fVec0_tmp[vsize + j3];
        }
        /* Recursive loop 1 */
        /* Pre code */
        for (int j0 = 0; j0 < 4; j0 = j0 + 1) {
            iRec1_tmp[j0] = iRec1_perm[j0];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iRec1[i] = 1103515245 * iRec1[i - 1] + 12345;
        }
        /* Post code */
        for (int j1 = 0; j1 < 4; j1 = j1 + 1) {
            iRec1_perm[j1] = iRec1_tmp[vsize + j1];
        }
        /* Recursive loop 2 */
        /* Pre code */
        for (int j4 = 0; j4 < 4; j4 = j4 + 1) {
            fRec2_tmp[j4] = fRec2_perm[j4];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec2[i] = fRec2[i - 1] + static_cast<double>((fSlow0 - fVec0[i - 1]) > 0.0) -
                       fSlow1 * static_cast<double>(fRec2[i - 1] > 0.0);
        }
        /* Post code */
        for (int j5 = 0; j5 < 4; j5 = j5 + 1) {
            fRec2_perm[j5] = fRec2_tmp[vsize + j5];
        }
        /* Recursive loop 3 */
        /* Pre code */
        fYec0_idx = (fYec0_idx + fYec0_idx_save) & 1023;
        for (int j6 = 0; j6 < 4; j6 = j6 + 1) {
            fRec0_tmp[j6] = fRec0_perm[j6];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec0[(i + fYec0_idx) & 1023] =
                fSlow2 * (fRec0[i - 1] + fRec0[i - 2]) +
                fSlow3 * static_cast<double>(iRec1[i]) * static_cast<double>(fRec2[i] > 0.0);
            fRec0[i] = fYec0[(i + fYec0_idx - iSlow4) & 1023];
        }
        /* Post code */
        fYec0_idx_save = vsize;
        for (int j7 = 0; j7 < 4; j7 = j7 + 1) {
            fRec0_perm[j7] = fRec0_tmp[vsize + j7];
        }
        /* Vectorizable loop 4 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            output0[i] = static_cast<FAUSTFLOAT>(fRec0[i]);
        }
    }
    /* Remaining frames */
    if (vindex < count) {
        FAUSTFLOAT* output0 = &output0_ptr[vindex];
        int         vsize   = count - vindex;
        /* Vectorizable loop 0 */
        /* Pre code */
        for (int j2 = 0; j2 < 4; j2 = j2 + 1) {
            fVec0_tmp[j2] = fVec0_perm[j2];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fVec0[i] = fSlow0;
        }
        /* Post code */
        for (int j3 = 0; j3 < 4; j3 = j3 + 1) {
            fVec0_perm[j3] = fVec0_tmp[vsize + j3];
        }
        /* Recursive loop 1 */
        /* Pre code */
        for (int j0 = 0; j0 < 4; j0 = j0 + 1) {
            iRec1_tmp[j0] = iRec1_perm[j0];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iRec1[i] = 1103515245 * iRec1[i - 1] + 12345;
        }
        /* Post code */
        for (int j1 = 0; j1 < 4; j1 = j1 + 1) {
            iRec1_perm[j1] = iRec1_tmp[vsize + j1];
        }
        /* Recursive loop 2 */
        /* Pre code */
        for (int j4 = 0; j4 < 4; j4 = j4 + 1) {
            fRec2_tmp[j4] = fRec2_perm[j4];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec2[i] = fRec2[i - 1] + static_cast<double>((fSlow0 - fVec0[i - 1]) > 0.0) -
                       fSlow1 * static_cast<double>(fRec2[i - 1] > 0.0);
        }
        /* Post code */
        for (int j5 = 0; j5 < 4; j5 = j5 + 1) {
            fRec2_perm[j5] = fRec2_tmp[vsize + j5];
        }
        /* Recursive loop 3 */
        /* Pre code */
        fYec0_idx = (fYec0_idx + fYec0_idx_save) & 1023;
        for (int j6 = 0; j6 < 4; j6 = j6 + 1) {
            fRec0_tmp[j6] = fRec0_perm[j6];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec0[(i + fYec0_idx) & 1023] =
                fSlow2 * (fRec0[i - 1] + fRec0[i - 2]) +
                fSlow3 * static_cast<double>(iRec1[i]) * static_cast<double>(fRec2[i] > 0.0);
            fRec0[i] = fYec0[(i + fYec0_idx - iSlow4) & 1023];
        }
        /* Post code */
        fYec0_idx_save = vsize;
        for (int j7 = 0; j7 < 4; j7 = j7 + 1) {
            fRec0_perm[j7] = fRec0_tmp[vsize + j7];
        }
        /* Vectorizable loop 4 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            output0[i] = static_cast<FAUSTFLOAT>(fRec0[i]);
        }
    }
}

virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs)
{
    FAUSTFLOAT* input0_ptr  = inputs[0];
    FAUSTFLOAT* output0_ptr = outputs[0];
    FAUSTFLOAT* output1_ptr = outputs[1];
    double  fSlow0 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * static_cast<double>(fVslider0));
    double  fRec0_tmp[36];
    double* fRec0  = &fRec0_tmp[4];
    double  fSlow1 = static_cast<double>(fVslider1);
    double  fSlow2 = ((fSlow1 > 0.0) ? std::exp(-(fConst1 / fSlow1)) : 0.0);
    double  fSlow3 = 4.4e+02 *
                     std::pow(2.0, 0.08333333333333333 * (static_cast<double>(fVslider2) + -49.0)) *
                     (1.0 - fSlow2);
    double  fRec2_tmp[36];
    double* fRec2 = &fRec2_tmp[4];
    double  fZec0[32];
    double  fZec1[32];
    double  fRec1_tmp[36];
    double* fRec1  = &fRec1_tmp[4];
    double  fSlow4 = 0.01 * static_cast<double>(fVslider3) + 1.0;
    double  fZec2[32];
    double  fZec3[32];
    double  fRec3_tmp[36];
    double* fRec3  = &fRec3_tmp[4];
    double  fSlow5 = 0.01 * static_cast<double>(fVslider4) + 1.0;
    double  fZec4[32];
    double  fZec5[32];
    double  fRec4_tmp[36];
    double* fRec4 = &fRec4_tmp[4];
    int     iRec5_tmp[36];
    int*    iRec5 = &iRec5_tmp[4];
    double  fZec6[32];
    double  fRec6_tmp[36];
    double* fRec6  = &fRec6_tmp[4];
    double  fSlow6 = fConst2 * static_cast<double>(fHslider0);
    double  fSlow7 = std::sin(fSlow6);
    double  fSlow8 = std::cos(fSlow6);
    double  fRec7_tmp[36];
    double* fRec7 = &fRec7_tmp[4];
    int     iVec0_tmp[36];
    int*    iVec0 = &iVec0_tmp[4];
    double  fZec7[32];
    double  fRec8_tmp[36];
    double* fRec8   = &fRec8_tmp[4];
    double  fSlow9  = static_cast<double>(fHslider1);
    double  fSlow10 = std::pow(1e+01, 0.05 * static_cast<double>(fHslider2));
    int     iSlow11 = static_cast<int>(static_cast<double>(fCheckbox0));
    int     iSlow12 = static_cast<int>(static_cast<double>(fCheckbox1));
    int     iSlow13 = static_cast<int>(static_cast<double>(fCheckbox2));
    int     iSlow14 = static_cast<int>(static_cast<double>(fEntry0) + -1.0);
    int     iSlow15 = iSlow14 >= 2;
    int     iSlow16 = iSlow14 >= 1;
    double  fZec8[32];
    double  fZec9[32];
    double  fZec10[32];
    double  fYec0_tmp[36];
    double* fYec0   = &fYec0_tmp[4];
    int     iSlow17 = iSlow14 >= 3;
    double  fZec11[32];
    double  fZec12[32];
    double  fYec1_tmp[36];
    double* fYec1 = &fYec1_tmp[4];
    double  fYec2_tmp[36];
    double* fYec2 = &fYec2_tmp[4];
    double  fZec13[32];
    double  fYec3_tmp[36];
    double* fYec3 = &fYec3_tmp[4];
    double  fYec4_tmp[36];
    double* fYec4 = &fYec4_tmp[4];
    double  fYec5_tmp[36];
    double* fYec5 = &fYec5_tmp[4];
    double  fZec14[32];
    double  fZec15[32];
    double  fYec6_tmp[36];
    double* fYec6 = &fYec6_tmp[4];
    double  fZec16[32];
    double  fYec7_tmp[36];
    double* fYec7 = &fYec7_tmp[4];
    double  fYec8_tmp[36];
    double* fYec8 = &fYec8_tmp[4];
    double  fYec9_tmp[36];
    double* fYec9 = &fYec9_tmp[4];
    double  fYec10_tmp[36];
    double* fYec10 = &fYec10_tmp[4];
    double  fYec11_tmp[36];
    double* fYec11 = &fYec11_tmp[4];
    double  fZec17[32];
    double  fZec18[32];
    double  fYec12_tmp[36];
    double* fYec12 = &fYec12_tmp[4];
    double  fZec19[32];
    double  fYec13_tmp[36];
    double* fYec13 = &fYec13_tmp[4];
    double  fYec14_tmp[36];
    double* fYec14 = &fYec14_tmp[4];
    double  fYec15_tmp[36];
    double* fYec15 = &fYec15_tmp[4];
    double  fYec16_tmp[36];
    double* fYec16 = &fYec16_tmp[4];
    double  fYec17_tmp[36];
    double* fYec17  = &fYec17_tmp[4];
    int     iSlow18 = static_cast<int>(static_cast<double>(fCheckbox3));
    double  fZec20[32];
    double  fZec21[32];
    double  fZec22[32];
    double  fSlow19 = 0.001 * static_cast<double>(fHslider3);
    double  fSlow20 = 0.0005 * static_cast<double>(fHslider4);
    double  fZec23[32];
    int     iZec24[32];
    double  fZec25[32];
    double  fRec9_tmp[36];
    double* fRec9   = &fRec9_tmp[4];
    double  fSlow21 = fConst2 * static_cast<double>(fHslider5);
    double  fSlow22 = std::sin(fSlow21);
    double  fSlow23 = std::cos(fSlow21);
    double  fRec15_tmp[36];
    double* fRec15 = &fRec15_tmp[4];
    double  fRec16_tmp[36];
    double* fRec16  = &fRec16_tmp[4];
    double  fSlow24 = std::pow(1e+01, 0.05 * static_cast<double>(fHslider6));
    int     iSlow25 = static_cast<int>(static_cast<double>(fCheckbox4));
    double  fSlow26 = static_cast<double>(fHslider7);
    double  fSlow27 = ((static_cast<int>(static_cast<double>(fCheckbox5))) ? -fSlow26 : fSlow26);
    double  fZec26[32];
    double  fZec27[32];
    double  fSlow28 = static_cast<double>(fHslider8);
    double  fSlow29 = std::exp(-(fConst6 * static_cast<double>(fHslider9)));
    double  fSlow30 = 2.0 * fSlow29;
    double  fSlow31 = static_cast<double>(fHslider10);
    double  fSlow32 = fConst1 * fSlow31;
    double  fSlow33 = static_cast<double>(fHslider11);
    double  fSlow34 = 6.283185307179586 * fSlow33;
    double  fSlow35 =
        3.141592653589793 * (fSlow33 - std::max<double>(fSlow33, static_cast<double>(fHslider12)));
    double  fZec28[32];
    double  fZec29[32];
    double  fSlow36 = mydsp_faustpower2_f(fSlow29);
    double  fRec14_tmp[36];
    double* fRec14  = &fRec14_tmp[4];
    double  fSlow37 = fConst1 * mydsp_faustpower2_f(fSlow31);
    double  fZec30[32];
    double  fRec13_tmp[36];
    double* fRec13  = &fRec13_tmp[4];
    double  fSlow38 = fConst1 * mydsp_faustpower3_f(fSlow31);
    double  fZec31[32];
    double  fRec12_tmp[36];
    double* fRec12  = &fRec12_tmp[4];
    double  fSlow39 = fConst1 * mydsp_faustpower4_f(fSlow31);
    double  fZec32[32];
    double  fRec11_tmp[36];
    double* fRec11 = &fRec11_tmp[4];
    double  fRec10_tmp[36];
    double* fRec10 = &fRec10_tmp[4];
    double  fZec33[32];
    double  fZec34[32];
    int     iZec35[32];
    double  fZec36[32];
    double  fRec17_tmp[36];
    double* fRec17 = &fRec17_tmp[4];
    double  fZec37[32];
    double  fZec38[32];
    double  fZec39[32];
    double  fZec40[32];
    double  fRec22_tmp[36];
    double* fRec22 = &fRec22_tmp[4];
    double  fZec41[32];
    double  fRec21_tmp[36];
    double* fRec21 = &fRec21_tmp[4];
    double  fZec42[32];
    double  fRec20_tmp[36];
    double* fRec20 = &fRec20_tmp[4];
    double  fZec43[32];
    double  fRec19_tmp[36];
    double* fRec19 = &fRec19_tmp[4];
    double  fRec18_tmp[36];
    double* fRec18  = &fRec18_tmp[4];
    double  fSlow40 = 0.5 * ((static_cast<int>(static_cast<double>(fCheckbox6)))
                                 ? 2.0
                                 : static_cast<double>(fHslider13));
    double  fSlow41 = 1.0 - fSlow40;
    double  fSlow42 = ((static_cast<int>(static_cast<double>(fCheckbox7))) ? -fSlow40 : fSlow40);
    double  fZec44[32];
    double  fZec45[32];
    double  fZec46[32];
    double  fRec26_tmp[36];
    double* fRec26 = &fRec26_tmp[4];
    double  fRec25_tmp[36];
    double* fRec25 = &fRec25_tmp[4];
    double  fRec24_tmp[36];
    double* fRec24  = &fRec24_tmp[4];
    double  fSlow43 = static_cast<double>(fHslider14);
    double  fSlow44 = (((0.001 * fSlow43) > 0.0) ? std::exp(-(fConst26 / fSlow43)) : 0.0);
    double  fSlow45 = 1.0 - fSlow44;
    double  fRec23_tmp[36];
    double* fRec23 = &fRec23_tmp[4];
    double  fRec33_tmp[36];
    double* fRec33 = &fRec33_tmp[4];
    double  fRec32_tmp[36];
    double* fRec32 = &fRec32_tmp[4];
    double  fRec31_tmp[36];
    double* fRec31 = &fRec31_tmp[4];
    double  fZec47[32];
    double  fRec30_tmp[36];
    double* fRec30 = &fRec30_tmp[4];
    double  fRec29_tmp[36];
    double* fRec29 = &fRec29_tmp[4];
    double  fRec28_tmp[36];
    double* fRec28 = &fRec28_tmp[4];
    double  fRec27_tmp[36];
    double* fRec27 = &fRec27_tmp[4];
    double  fRec40_tmp[36];
    double* fRec40 = &fRec40_tmp[4];
    double  fRec39_tmp[36];
    double* fRec39 = &fRec39_tmp[4];
    double  fRec38_tmp[36];
    double* fRec38 = &fRec38_tmp[4];
    double  fZec48[32];
    double  fRec37_tmp[36];
    double* fRec37 = &fRec37_tmp[4];
    double  fRec36_tmp[36];
    double* fRec36 = &fRec36_tmp[4];
    double  fRec35_tmp[36];
    double* fRec35 = &fRec35_tmp[4];
    double  fRec34_tmp[36];
    double* fRec34 = &fRec34_tmp[4];
    double  fRec47_tmp[36];
    double* fRec47 = &fRec47_tmp[4];
    double  fRec46_tmp[36];
    double* fRec46 = &fRec46_tmp[4];
    double  fRec45_tmp[36];
    double* fRec45 = &fRec45_tmp[4];
    double  fZec49[32];
    double  fRec44_tmp[36];
    double* fRec44 = &fRec44_tmp[4];
    double  fRec43_tmp[36];
    double* fRec43 = &fRec43_tmp[4];
    double  fRec42_tmp[36];
    double* fRec42 = &fRec42_tmp[4];
    double  fRec41_tmp[36];
    double* fRec41 = &fRec41_tmp[4];
    double  fRec54_tmp[36];
    double* fRec54 = &fRec54_tmp[4];
    double  fRec53_tmp[36];
    double* fRec53 = &fRec53_tmp[4];
    double  fRec52_tmp[36];
    double* fRec52 = &fRec52_tmp[4];
    double  fZec50[32];
    double  fRec51_tmp[36];
    double* fRec51 = &fRec51_tmp[4];
    double  fRec50_tmp[36];
    double* fRec50 = &fRec50_tmp[4];
    double  fRec49_tmp[36];
    double* fRec49 = &fRec49_tmp[4];
    double  fRec48_tmp[36];
    double* fRec48 = &fRec48_tmp[4];
    double  fRec61_tmp[36];
    double* fRec61 = &fRec61_tmp[4];
    double  fRec60_tmp[36];
    double* fRec60 = &fRec60_tmp[4];
    double  fRec59_tmp[36];
    double* fRec59 = &fRec59_tmp[4];
    double  fZec51[32];
    double  fRec58_tmp[36];
    double* fRec58 = &fRec58_tmp[4];
    double  fRec57_tmp[36];
    double* fRec57 = &fRec57_tmp[4];
    double  fRec56_tmp[36];
    double* fRec56 = &fRec56_tmp[4];
    double  fRec55_tmp[36];
    double* fRec55 = &fRec55_tmp[4];
    double  fRec68_tmp[36];
    double* fRec68 = &fRec68_tmp[4];
    double  fRec67_tmp[36];
    double* fRec67 = &fRec67_tmp[4];
    double  fRec66_tmp[36];
    double* fRec66 = &fRec66_tmp[4];
    double  fZec52[32];
    double  fRec65_tmp[36];
    double* fRec65 = &fRec65_tmp[4];
    double  fRec64_tmp[36];
    double* fRec64 = &fRec64_tmp[4];
    double  fRec63_tmp[36];
    double* fRec63 = &fRec63_tmp[4];
    double  fRec62_tmp[36];
    double* fRec62 = &fRec62_tmp[4];
    double  fRec75_tmp[36];
    double* fRec75 = &fRec75_tmp[4];
    double  fRec74_tmp[36];
    double* fRec74 = &fRec74_tmp[4];
    double  fRec73_tmp[36];
    double* fRec73 = &fRec73_tmp[4];
    double  fZec53[32];
    double  fRec72_tmp[36];
    double* fRec72 = &fRec72_tmp[4];
    double  fRec71_tmp[36];
    double* fRec71 = &fRec71_tmp[4];
    double  fRec70_tmp[36];
    double* fRec70 = &fRec70_tmp[4];
    double  fRec69_tmp[36];
    double* fRec69 = &fRec69_tmp[4];
    double  fRec82_tmp[36];
    double* fRec82 = &fRec82_tmp[4];
    double  fRec81_tmp[36];
    double* fRec81 = &fRec81_tmp[4];
    double  fRec80_tmp[36];
    double* fRec80 = &fRec80_tmp[4];
    double  fZec54[32];
    double  fRec79_tmp[36];
    double* fRec79 = &fRec79_tmp[4];
    double  fRec78_tmp[36];
    double* fRec78 = &fRec78_tmp[4];
    double  fRec77_tmp[36];
    double* fRec77 = &fRec77_tmp[4];
    double  fRec76_tmp[36];
    double* fRec76 = &fRec76_tmp[4];
    double  fRec89_tmp[36];
    double* fRec89 = &fRec89_tmp[4];
    double  fRec88_tmp[36];
    double* fRec88 = &fRec88_tmp[4];
    double  fRec87_tmp[36];
    double* fRec87 = &fRec87_tmp[4];
    double  fZec55[32];
    double  fRec86_tmp[36];
    double* fRec86 = &fRec86_tmp[4];
    double  fRec85_tmp[36];
    double* fRec85 = &fRec85_tmp[4];
    double  fRec84_tmp[36];
    double* fRec84 = &fRec84_tmp[4];
    double  fRec83_tmp[36];
    double* fRec83 = &fRec83_tmp[4];
    double  fRec96_tmp[36];
    double* fRec96 = &fRec96_tmp[4];
    double  fRec95_tmp[36];
    double* fRec95 = &fRec95_tmp[4];
    double  fRec94_tmp[36];
    double* fRec94 = &fRec94_tmp[4];
    double  fZec56[32];
    double  fRec93_tmp[36];
    double* fRec93 = &fRec93_tmp[4];
    double  fRec92_tmp[36];
    double* fRec92 = &fRec92_tmp[4];
    double  fRec91_tmp[36];
    double* fRec91 = &fRec91_tmp[4];
    double  fRec90_tmp[36];
    double* fRec90 = &fRec90_tmp[4];
    double  fRec103_tmp[36];
    double* fRec103 = &fRec103_tmp[4];
    double  fRec102_tmp[36];
    double* fRec102 = &fRec102_tmp[4];
    double  fRec101_tmp[36];
    double* fRec101 = &fRec101_tmp[4];
    double  fZec57[32];
    double  fRec100_tmp[36];
    double* fRec100 = &fRec100_tmp[4];
    double  fRec99_tmp[36];
    double* fRec99 = &fRec99_tmp[4];
    double  fRec98_tmp[36];
    double* fRec98 = &fRec98_tmp[4];
    double  fRec97_tmp[36];
    double* fRec97 = &fRec97_tmp[4];
    double  fRec110_tmp[36];
    double* fRec110 = &fRec110_tmp[4];
    double  fRec109_tmp[36];
    double* fRec109 = &fRec109_tmp[4];
    double  fRec108_tmp[36];
    double* fRec108 = &fRec108_tmp[4];
    double  fZec58[32];
    double  fRec107_tmp[36];
    double* fRec107 = &fRec107_tmp[4];
    double  fRec106_tmp[36];
    double* fRec106 = &fRec106_tmp[4];
    double  fRec105_tmp[36];
    double* fRec105 = &fRec105_tmp[4];
    double  fRec104_tmp[36];
    double* fRec104 = &fRec104_tmp[4];
    double  fRec117_tmp[36];
    double* fRec117 = &fRec117_tmp[4];
    double  fRec116_tmp[36];
    double* fRec116 = &fRec116_tmp[4];
    double  fRec115_tmp[36];
    double* fRec115 = &fRec115_tmp[4];
    double  fZec59[32];
    double  fRec114_tmp[36];
    double* fRec114 = &fRec114_tmp[4];
    double  fRec113_tmp[36];
    double* fRec113 = &fRec113_tmp[4];
    double  fRec112_tmp[36];
    double* fRec112 = &fRec112_tmp[4];
    double  fRec111_tmp[36];
    double* fRec111 = &fRec111_tmp[4];
    double  fRec121_tmp[36];
    double* fRec121 = &fRec121_tmp[4];
    double  fRec120_tmp[36];
    double* fRec120 = &fRec120_tmp[4];
    double  fRec119_tmp[36];
    double* fRec119 = &fRec119_tmp[4];
    double  fRec118_tmp[36];
    double* fRec118 = &fRec118_tmp[4];
    double  fSlow46 = static_cast<double>(fHslider15);
    int     vindex  = 0;
    /* Main loop */
    for (vindex = 0; vindex <= (count - 32); vindex = vindex + 32) {
        FAUSTFLOAT* input0  = &input0_ptr[vindex];
        FAUSTFLOAT* output0 = &output0_ptr[vindex];
        FAUSTFLOAT* output1 = &output1_ptr[vindex];
        int         vsize   = 32;
        /* Recursive loop 0 */
        /* Pre code */
        for (int j2 = 0; j2 < 4; j2 = j2 + 1) {
            fRec2_tmp[j2] = fRec2_perm[j2];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec2[i] = fRec2[i - 1] * fSlow2 + fSlow3;
        }
        /* Post code */
        for (int j3 = 0; j3 < 4; j3 = j3 + 1) {
            fRec2_perm[j3] = fRec2_tmp[vsize + j3];
        }
        /* Vectorizable loop 1 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec0[i] = std::max<double>(2e+01, std::fabs(fRec2[i]));
        }
        /* Vectorizable loop 2 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec2[i] = std::max<double>(2e+01, std::fabs(fSlow4 * fRec2[i]));
        }
        /* Vectorizable loop 3 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec4[i] = std::max<double>(2e+01, std::fabs(fSlow5 * fRec2[i]));
        }
        /* Recursive loop 4 */
        /* Pre code */
        for (int j4 = 0; j4 < 4; j4 = j4 + 1) {
            fRec1_tmp[j4] = fRec1_perm[j4];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec1[i] = fRec1[i - 1] + fConst1 * fZec0[i];
            fRec1[i] = fZec1[i] - std::floor(fZec1[i]);
        }
        /* Post code */
        for (int j5 = 0; j5 < 4; j5 = j5 + 1) {
            fRec1_perm[j5] = fRec1_tmp[vsize + j5];
        }
        /* Recursive loop 5 */
        /* Pre code */
        for (int j6 = 0; j6 < 4; j6 = j6 + 1) {
            fRec3_tmp[j6] = fRec3_perm[j6];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec3[i] = fRec3[i - 1] + fConst1 * fZec2[i];
            fRec3[i] = fZec3[i] - std::floor(fZec3[i]);
        }
        /* Post code */
        for (int j7 = 0; j7 < 4; j7 = j7 + 1) {
            fRec3_perm[j7] = fRec3_tmp[vsize + j7];
        }
        /* Recursive loop 6 */
        /* Pre code */
        for (int j8 = 0; j8 < 4; j8 = j8 + 1) {
            fRec4_tmp[j8] = fRec4_perm[j8];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec5[i] = fRec4[i - 1] + fConst1 * fZec4[i];
            fRec4[i] = fZec5[i] - std::floor(fZec5[i]);
        }
        /* Post code */
        for (int j9 = 0; j9 < 4; j9 = j9 + 1) {
            fRec4_perm[j9] = fRec4_tmp[vsize + j9];
        }
        /* Vectorizable loop 7 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec8[i] = 2.0 * fRec1[i];
        }
        /* Vectorizable loop 8 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec14[i] = 2.0 * fRec3[i];
        }
        /* Vectorizable loop 9 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec17[i] = 2.0 * fRec4[i];
        }
        /* Vectorizable loop 10 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec9[i] = fZec8[i] + -1.0;
        }
        /* Vectorizable loop 11 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec15[i] = fZec14[i] + -1.0;
        }
        /* Vectorizable loop 12 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec18[i] = fZec17[i] + -1.0;
        }
        /* Vectorizable loop 13 */
        /* Pre code */
        for (int j20 = 0; j20 < 4; j20 = j20 + 1) {
            fYec0_tmp[j20] = fYec0_perm[j20];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec0[i] = mydsp_faustpower2_f(fZec9[i]);
        }
        /* Post code */
        for (int j21 = 0; j21 < 4; j21 = j21 + 1) {
            fYec0_perm[j21] = fYec0_tmp[vsize + j21];
        }
        /* Vectorizable loop 14 */
        /* Pre code */
        for (int j32 = 0; j32 < 4; j32 = j32 + 1) {
            fYec6_tmp[j32] = fYec6_perm[j32];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec6[i] = mydsp_faustpower2_f(fZec15[i]);
        }
        /* Post code */
        for (int j33 = 0; j33 < 4; j33 = j33 + 1) {
            fYec6_perm[j33] = fYec6_tmp[vsize + j33];
        }
        /* Vectorizable loop 15 */
        /* Pre code */
        for (int j44 = 0; j44 < 4; j44 = j44 + 1) {
            fYec12_tmp[j44] = fYec12_perm[j44];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec12[i] = mydsp_faustpower2_f(fZec18[i]);
        }
        /* Post code */
        for (int j45 = 0; j45 < 4; j45 = j45 + 1) {
            fYec12_perm[j45] = fYec12_tmp[vsize + j45];
        }
        /* Recursive loop 16 */
        /* Pre code */
        for (int j10 = 0; j10 < 4; j10 = j10 + 1) {
            iRec5_tmp[j10] = iRec5_perm[j10];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iRec5[i] = 1103515245 * iRec5[i - 1] + 12345;
        }
        /* Post code */
        for (int j11 = 0; j11 < 4; j11 = j11 + 1) {
            iRec5_perm[j11] = iRec5_tmp[vsize + j11];
        }
        /* Vectorizable loop 17 */
        /* Pre code */
        for (int j16 = 0; j16 < 4; j16 = j16 + 1) {
            iVec0_tmp[j16] = iVec0_perm[j16];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iVec0[i] = 1;
        }
        /* Post code */
        for (int j17 = 0; j17 < 4; j17 = j17 + 1) {
            iVec0_perm[j17] = iVec0_tmp[vsize + j17];
        }
        /* Vectorizable loop 18 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec12[i] = mydsp_faustpower3_f(fZec9[i]);
        }
        /* Vectorizable loop 19 */
        /* Pre code */
        for (int j26 = 0; j26 < 4; j26 = j26 + 1) {
            fYec3_tmp[j26] = fYec3_perm[j26];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec3[i] = fYec0[i] * (fYec0[i] + -2.0);
        }
        /* Post code */
        for (int j27 = 0; j27 < 4; j27 = j27 + 1) {
            fYec3_perm[j27] = fYec3_tmp[vsize + j27];
        }
        /* Vectorizable loop 20 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec16[i] = mydsp_faustpower3_f(fZec15[i]);
        }
        /* Vectorizable loop 21 */
        /* Pre code */
        for (int j38 = 0; j38 < 4; j38 = j38 + 1) {
            fYec9_tmp[j38] = fYec9_perm[j38];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec9[i] = fYec6[i] * (fYec6[i] + -2.0);
        }
        /* Post code */
        for (int j39 = 0; j39 < 4; j39 = j39 + 1) {
            fYec9_perm[j39] = fYec9_tmp[vsize + j39];
        }
        /* Vectorizable loop 22 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec19[i] = mydsp_faustpower3_f(fZec18[i]);
        }
        /* Vectorizable loop 23 */
        /* Pre code */
        for (int j50 = 0; j50 < 4; j50 = j50 + 1) {
            fYec15_tmp[j50] = fYec15_perm[j50];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec15[i] = fYec12[i] * (fYec12[i] + -2.0);
        }
        /* Post code */
        for (int j51 = 0; j51 < 4; j51 = j51 + 1) {
            fYec15_perm[j51] = fYec15_tmp[vsize + j51];
        }
        /* Vectorizable loop 24 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec6[i] = 4.656612875245797e-10 * static_cast<double>(iRec5[i]);
        }
        /* Vectorizable loop 25 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec7[i] = static_cast<double>(1 - iVec0[i - 1]);
        }
        /* Vectorizable loop 26 */
        /* Pre code */
        for (int j22 = 0; j22 < 4; j22 = j22 + 1) {
            fYec1_tmp[j22] = fYec1_perm[j22];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec1[i] = fZec12[i] + (1.0 - fZec8[i]);
        }
        /* Post code */
        for (int j23 = 0; j23 < 4; j23 = j23 + 1) {
            fYec1_perm[j23] = fYec1_tmp[vsize + j23];
        }
        /* Vectorizable loop 27 */
        /* Pre code */
        for (int j28 = 0; j28 < 4; j28 = j28 + 1) {
            fYec4_tmp[j28] = fYec4_perm[j28];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec4[i] = (fYec3[i] - fYec3[i - 1]) / fZec0[i];
        }
        /* Post code */
        for (int j29 = 0; j29 < 4; j29 = j29 + 1) {
            fYec4_perm[j29] = fYec4_tmp[vsize + j29];
        }
        /* Vectorizable loop 28 */
        /* Pre code */
        for (int j34 = 0; j34 < 4; j34 = j34 + 1) {
            fYec7_tmp[j34] = fYec7_perm[j34];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec7[i] = fZec16[i] + (1.0 - fZec14[i]);
        }
        /* Post code */
        for (int j35 = 0; j35 < 4; j35 = j35 + 1) {
            fYec7_perm[j35] = fYec7_tmp[vsize + j35];
        }
        /* Vectorizable loop 29 */
        /* Pre code */
        for (int j40 = 0; j40 < 4; j40 = j40 + 1) {
            fYec10_tmp[j40] = fYec10_perm[j40];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec10[i] = (fYec9[i] - fYec9[i - 1]) / fZec2[i];
        }
        /* Post code */
        for (int j41 = 0; j41 < 4; j41 = j41 + 1) {
            fYec10_perm[j41] = fYec10_tmp[vsize + j41];
        }
        /* Vectorizable loop 30 */
        /* Pre code */
        for (int j46 = 0; j46 < 4; j46 = j46 + 1) {
            fYec13_tmp[j46] = fYec13_perm[j46];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec13[i] = fZec19[i] + (1.0 - fZec17[i]);
        }
        /* Post code */
        for (int j47 = 0; j47 < 4; j47 = j47 + 1) {
            fYec13_perm[j47] = fYec13_tmp[vsize + j47];
        }
        /* Vectorizable loop 31 */
        /* Pre code */
        for (int j52 = 0; j52 < 4; j52 = j52 + 1) {
            fYec16_tmp[j52] = fYec16_perm[j52];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec16[i] = (fYec15[i] - fYec15[i - 1]) / fZec4[i];
        }
        /* Post code */
        for (int j53 = 0; j53 < 4; j53 = j53 + 1) {
            fYec16_perm[j53] = fYec16_tmp[vsize + j53];
        }
        /* Recursive loop 32 */
        /* Pre code */
        for (int j0 = 0; j0 < 4; j0 = j0 + 1) {
            fRec0_tmp[j0] = fRec0_perm[j0];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec0[i] = fSlow0 + 0.999 * fRec0[i - 1];
        }
        /* Post code */
        for (int j1 = 0; j1 < 4; j1 = j1 + 1) {
            fRec0_perm[j1] = fRec0_tmp[vsize + j1];
        }
        /* Recursive loop 33 */
        /* Pre code */
        for (int j12 = 0; j12 < 4; j12 = j12 + 1) {
            fRec6_tmp[j12] = fRec6_perm[j12];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec6[i] = 0.5221894 * fRec6[i - 3] + fZec6[i] + 2.494956002 * fRec6[i - 1] -
                       2.017265875 * fRec6[i - 2];
        }
        /* Post code */
        for (int j13 = 0; j13 < 4; j13 = j13 + 1) {
            fRec6_perm[j13] = fRec6_tmp[vsize + j13];
        }
        /* Recursive loop 34 */
        /* Pre code */
        for (int j14 = 0; j14 < 4; j14 = j14 + 1) {
            fRec7_tmp[j14] = fRec7_perm[j14];
        }
        for (int j18 = 0; j18 < 4; j18 = j18 + 1) {
            fRec8_tmp[j18] = fRec8_perm[j18];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec7[i] = fSlow7 * fRec8[i - 1] + fSlow8 * fRec7[i - 1];
            fRec8[i] = fZec7[i] + fSlow8 * fRec8[i - 1] - fSlow7 * fRec7[i - 1];
        }
        /* Post code */
        for (int j15 = 0; j15 < 4; j15 = j15 + 1) {
            fRec7_perm[j15] = fRec7_tmp[vsize + j15];
        }
        for (int j19 = 0; j19 < 4; j19 = j19 + 1) {
            fRec8_perm[j19] = fRec8_tmp[vsize + j19];
        }
        /* Vectorizable loop 35 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec10[i] = static_cast<double>(iVec0[i - 1]);
        }
        /* Vectorizable loop 36 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec11[i] = static_cast<double>(iVec0[i - 2]);
        }
        /* Vectorizable loop 37 */
        /* Pre code */
        for (int j24 = 0; j24 < 4; j24 = j24 + 1) {
            fYec2_tmp[j24] = fYec2_perm[j24];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec2[i] = (fZec12[i] + (1.0 - (fZec8[i] + fYec1[i - 1]))) / fZec0[i];
        }
        /* Post code */
        for (int j25 = 0; j25 < 4; j25 = j25 + 1) {
            fYec2_perm[j25] = fYec2_tmp[vsize + j25];
        }
        /* Vectorizable loop 38 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec13[i] = static_cast<double>(iVec0[i - 3]);
        }
        /* Vectorizable loop 39 */
        /* Pre code */
        for (int j30 = 0; j30 < 4; j30 = j30 + 1) {
            fYec5_tmp[j30] = fYec5_perm[j30];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec5[i] = (fYec4[i] - fYec4[i - 1]) / fZec0[i];
        }
        /* Post code */
        for (int j31 = 0; j31 < 4; j31 = j31 + 1) {
            fYec5_perm[j31] = fYec5_tmp[vsize + j31];
        }
        /* Vectorizable loop 40 */
        /* Pre code */
        for (int j36 = 0; j36 < 4; j36 = j36 + 1) {
            fYec8_tmp[j36] = fYec8_perm[j36];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec8[i] = (fZec16[i] + (1.0 - (fZec14[i] + fYec7[i - 1]))) / fZec2[i];
        }
        /* Post code */
        for (int j37 = 0; j37 < 4; j37 = j37 + 1) {
            fYec8_perm[j37] = fYec8_tmp[vsize + j37];
        }
        /* Vectorizable loop 41 */
        /* Pre code */
        for (int j42 = 0; j42 < 4; j42 = j42 + 1) {
            fYec11_tmp[j42] = fYec11_perm[j42];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec11[i] = (fYec10[i] - fYec10[i - 1]) / fZec2[i];
        }
        /* Post code */
        for (int j43 = 0; j43 < 4; j43 = j43 + 1) {
            fYec11_perm[j43] = fYec11_tmp[vsize + j43];
        }
        /* Vectorizable loop 42 */
        /* Pre code */
        for (int j48 = 0; j48 < 4; j48 = j48 + 1) {
            fYec14_tmp[j48] = fYec14_perm[j48];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec14[i] = (fZec19[i] + (1.0 - (fZec17[i] + fYec13[i - 1]))) / fZec4[i];
        }
        /* Post code */
        for (int j49 = 0; j49 < 4; j49 = j49 + 1) {
            fYec14_perm[j49] = fYec14_tmp[vsize + j49];
        }
        /* Vectorizable loop 43 */
        /* Pre code */
        for (int j54 = 0; j54 < 4; j54 = j54 + 1) {
            fYec17_tmp[j54] = fYec17_perm[j54];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec17[i] = (fYec16[i] - fYec16[i - 1]) / fZec4[i];
        }
        /* Post code */
        for (int j55 = 0; j55 < 4; j55 = j55 + 1) {
            fYec17_perm[j55] = fYec17_tmp[vsize + j55];
        }
        /* Vectorizable loop 44 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec20[i] =
                fRec0[i] *
                ((iSlow12)
                     ? static_cast<double>(input0[i])
                     : ((iSlow13)
                            ? ((iSlow18)
                                   ? 0.049922035 * fRec6[i] + 0.050612699 * fRec6[i - 2] -
                                         (0.095993537 * fRec6[i - 1] + 0.004408786 * fRec6[i - 3])
                                   : fZec6[i])
                            : 0.3333333333333333 * fRec0[i] *
                                  (((iSlow15)
                                        ? ((iSlow17)
                                               ? fConst5 * (fZec13[i] * (fYec5[i] - fYec5[i - 1]) /
                                                            fZec0[i])
                                               : fConst4 * (fZec11[i] * (fYec2[i] - fYec2[i - 1]) /
                                                            fZec0[i]))
                                        : ((iSlow16)
                                               ? fConst3 * (fZec10[i] * (fYec0[i] - fYec0[i - 1]) /
                                                            fZec0[i])
                                               : fZec9[i])) +
                                   ((iSlow15)
                                        ? ((iSlow17)
                                               ? fConst5 * (fZec13[i] *
                                                            (fYec11[i] - fYec11[i - 1]) / fZec2[i])
                                               : fConst4 * (fZec11[i] * (fYec8[i] - fYec8[i - 1]) /
                                                            fZec2[i]))
                                        : ((iSlow16)
                                               ? fConst3 * (fZec10[i] * (fYec6[i] - fYec6[i - 1]) /
                                                            fZec2[i])
                                               : fZec15[i])) +
                                   ((iSlow15)
                                        ? ((iSlow17)
                                               ? fConst5 * (fZec13[i] *
                                                            (fYec17[i] - fYec17[i - 1]) / fZec4[i])
                                               : fConst4 * (fZec11[i] *
                                                            (fYec14[i] - fYec14[i - 1]) / fZec4[i]))
                                        : ((iSlow16)
                                               ? fConst3 * (fZec10[i] *
                                                            (fYec12[i] - fYec12[i - 1]) / fZec4[i])
                                               : fZec18[i])))));
        }
        /* Vectorizable loop 45 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec23[i] = fConst0 * (fSlow19 + fSlow20 * (fRec7[i] + 1.0));
        }
        /* Vectorizable loop 46 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec34[i] = fConst0 * (fSlow19 + fSlow20 * (fRec8[i] + 1.0));
        }
        /* Vectorizable loop 47 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec21[i] = ((iSlow11) ? 0.0 : fZec20[i]);
        }
        /* Vectorizable loop 48 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iZec24[i] = static_cast<int>(fZec23[i]);
        }
        /* Vectorizable loop 49 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iZec35[i] = static_cast<int>(fZec34[i]);
        }
        /* Vectorizable loop 50 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fHbargraph0 = static_cast<FAUSTFLOAT>(fRec8[i] + fRec7[i]);
            fZec22[i]   = fSlow10 * fZec21[i];
        }
        /* Vectorizable loop 51 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec25[i] = static_cast<double>(iZec24[i]);
        }
        /* Vectorizable loop 52 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec33[i] = fSlow10 * fZec21[i];
        }
        /* Vectorizable loop 53 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec36[i] = static_cast<double>(iZec35[i]);
        }
        /* Recursive loop 54 */
        /* Pre code */
        fYec18_idx = (fYec18_idx + fYec18_idx_save) & 4095;
        for (int j56 = 0; j56 < 4; j56 = j56 + 1) {
            fRec9_tmp[j56] = fRec9_perm[j56];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec18[(i + fYec18_idx) & 4095] = fSlow9 * fRec9[i - 1] - fZec22[i];
            fRec9[i] = fYec18[(i + fYec18_idx - (iZec24[i] & 2047)) & 4095] *
                           (fZec25[i] + (1.0 - fZec23[i])) +
                       (fZec23[i] - fZec25[i]) *
                           fYec18[(i + fYec18_idx - ((iZec24[i] + 1) & 2047)) & 4095];
        }
        /* Post code */
        fYec18_idx_save = vsize;
        for (int j57 = 0; j57 < 4; j57 = j57 + 1) {
            fRec9_perm[j57] = fRec9_tmp[vsize + j57];
        }
        /* Recursive loop 55 */
        /* Pre code */
        fYec19_idx = (fYec19_idx + fYec19_idx_save) & 4095;
        for (int j72 = 0; j72 < 4; j72 = j72 + 1) {
            fRec17_tmp[j72] = fRec17_perm[j72];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec19[(i + fYec19_idx) & 4095] = fSlow9 * fRec17[i - 1] - fZec33[i];
            fRec17[i] = fYec19[(i + fYec19_idx - (iZec35[i] & 2047)) & 4095] *
                            (fZec36[i] + (1.0 - fZec34[i])) +
                        (fZec34[i] - fZec36[i]) *
                            fYec19[(i + fYec19_idx - ((iZec35[i] + 1) & 2047)) & 4095];
        }
        /* Post code */
        fYec19_idx_save = vsize;
        for (int j73 = 0; j73 < 4; j73 = j73 + 1) {
            fRec17_perm[j73] = fRec17_tmp[vsize + j73];
        }
        /* Recursive loop 56 */
        /* Pre code */
        for (int j58 = 0; j58 < 4; j58 = j58 + 1) {
            fRec15_tmp[j58] = fRec15_perm[j58];
        }
        for (int j60 = 0; j60 < 4; j60 = j60 + 1) {
            fRec16_tmp[j60] = fRec16_perm[j60];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec15[i] = fSlow22 * fRec16[i - 1] + fSlow23 * fRec15[i - 1];
            fRec16[i] = fZec7[i] + fSlow23 * fRec16[i - 1] - fSlow22 * fRec15[i - 1];
        }
        /* Post code */
        for (int j59 = 0; j59 < 4; j59 = j59 + 1) {
            fRec15_perm[j59] = fRec15_tmp[vsize + j59];
        }
        for (int j61 = 0; j61 < 4; j61 = j61 + 1) {
            fRec16_perm[j61] = fRec16_tmp[vsize + j61];
        }
        /* Vectorizable loop 57 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec26[i] = ((iSlow11) ? fZec20[i] : 0.5 * (fZec22[i] + fRec9[i] * fSlow27));
        }
        /* Vectorizable loop 58 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec37[i] = ((iSlow11) ? fZec20[i] : 0.5 * (fZec33[i] + fRec17[i] * fSlow27));
        }
        /* Vectorizable loop 59 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec27[i] = ((iSlow25) ? 0.0 : fZec26[i]);
        }
        /* Vectorizable loop 60 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec28[i] = fSlow34 - fSlow35 * (1.0 - fRec15[i]);
        }
        /* Vectorizable loop 61 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec38[i] = ((iSlow25) ? 0.0 : fZec37[i]);
        }
        /* Vectorizable loop 62 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec39[i] = fSlow34 - fSlow35 * (1.0 - fRec16[i]);
        }
        /* Recursive loop 63 */
        /* Pre code */
        for (int j62 = 0; j62 < 4; j62 = j62 + 1) {
            fRec14_tmp[j62] = fRec14_perm[j62];
        }
        for (int j64 = 0; j64 < 4; j64 = j64 + 1) {
            fRec13_tmp[j64] = fRec13_perm[j64];
        }
        for (int j66 = 0; j66 < 4; j66 = j66 + 1) {
            fRec12_tmp[j66] = fRec12_perm[j66];
        }
        for (int j68 = 0; j68 < 4; j68 = j68 + 1) {
            fRec11_tmp[j68] = fRec11_perm[j68];
        }
        for (int j70 = 0; j70 < 4; j70 = j70 + 1) {
            fRec10_tmp[j70] = fRec10_perm[j70];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec29[i] = fRec14[i - 1] * std::cos(fSlow32 * fZec28[i]);
            fRec14[i] = fSlow24 * fZec27[i] + fSlow28 * fRec10[i - 1] + fSlow30 * fZec29[i] -
                        fSlow36 * fRec14[i - 2];
            fZec30[i] = fRec13[i - 1] * std::cos(fSlow37 * fZec28[i]);
            fRec13[i] = fRec14[i - 2] + fSlow36 * (fRec14[i] - fRec13[i - 2]) -
                        fSlow30 * (fZec29[i] - fZec30[i]);
            fZec31[i] = fRec12[i - 1] * std::cos(fSlow38 * fZec28[i]);
            fRec12[i] = fRec13[i - 2] + fSlow36 * (fRec13[i] - fRec12[i - 2]) -
                        fSlow30 * (fZec30[i] - fZec31[i]);
            fZec32[i] = fRec11[i - 1] * std::cos(fSlow39 * fZec28[i]);
            fRec11[i] = fRec12[i - 2] + fSlow36 * (fRec12[i] - fRec11[i - 2]) -
                        fSlow30 * (fZec31[i] - fZec32[i]);
            fRec10[i] = fRec11[i - 2] + fSlow36 * fRec11[i] - fSlow30 * fZec32[i];
        }
        /* Post code */
        for (int j63 = 0; j63 < 4; j63 = j63 + 1) {
            fRec14_perm[j63] = fRec14_tmp[vsize + j63];
        }
        for (int j65 = 0; j65 < 4; j65 = j65 + 1) {
            fRec13_perm[j65] = fRec13_tmp[vsize + j65];
        }
        for (int j67 = 0; j67 < 4; j67 = j67 + 1) {
            fRec12_perm[j67] = fRec12_tmp[vsize + j67];
        }
        for (int j69 = 0; j69 < 4; j69 = j69 + 1) {
            fRec11_perm[j69] = fRec11_tmp[vsize + j69];
        }
        for (int j71 = 0; j71 < 4; j71 = j71 + 1) {
            fRec10_perm[j71] = fRec10_tmp[vsize + j71];
        }
        /* Recursive loop 64 */
        /* Pre code */
        for (int j74 = 0; j74 < 4; j74 = j74 + 1) {
            fRec22_tmp[j74] = fRec22_perm[j74];
        }
        for (int j76 = 0; j76 < 4; j76 = j76 + 1) {
            fRec21_tmp[j76] = fRec21_perm[j76];
        }
        for (int j78 = 0; j78 < 4; j78 = j78 + 1) {
            fRec20_tmp[j78] = fRec20_perm[j78];
        }
        for (int j80 = 0; j80 < 4; j80 = j80 + 1) {
            fRec19_tmp[j80] = fRec19_perm[j80];
        }
        for (int j82 = 0; j82 < 4; j82 = j82 + 1) {
            fRec18_tmp[j82] = fRec18_perm[j82];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec40[i] = fRec22[i - 1] * std::cos(fSlow32 * fZec39[i]);
            fRec22[i] = fSlow24 * fZec38[i] + fSlow28 * fRec18[i - 1] + fSlow30 * fZec40[i] -
                        fSlow36 * fRec22[i - 2];
            fZec41[i] = fRec21[i - 1] * std::cos(fSlow37 * fZec39[i]);
            fRec21[i] = fRec22[i - 2] + fSlow36 * (fRec22[i] - fRec21[i - 2]) -
                        fSlow30 * (fZec40[i] - fZec41[i]);
            fZec42[i] = fRec20[i - 1] * std::cos(fSlow38 * fZec39[i]);
            fRec20[i] = fRec21[i - 2] + fSlow36 * (fRec21[i] - fRec20[i - 2]) -
                        fSlow30 * (fZec41[i] - fZec42[i]);
            fZec43[i] = fRec19[i - 1] * std::cos(fSlow39 * fZec39[i]);
            fRec19[i] = fRec20[i - 2] + fSlow36 * (fRec20[i] - fRec19[i - 2]) -
                        fSlow30 * (fZec42[i] - fZec43[i]);
            fRec18[i] = fRec19[i - 2] + fSlow36 * fRec19[i] - fSlow30 * fZec43[i];
        }
        /* Post code */
        for (int j75 = 0; j75 < 4; j75 = j75 + 1) {
            fRec22_perm[j75] = fRec22_tmp[vsize + j75];
        }
        for (int j77 = 0; j77 < 4; j77 = j77 + 1) {
            fRec21_perm[j77] = fRec21_tmp[vsize + j77];
        }
        for (int j79 = 0; j79 < 4; j79 = j79 + 1) {
            fRec20_perm[j79] = fRec20_tmp[vsize + j79];
        }
        for (int j81 = 0; j81 < 4; j81 = j81 + 1) {
            fRec19_perm[j81] = fRec19_tmp[vsize + j81];
        }
        for (int j83 = 0; j83 < 4; j83 = j83 + 1) {
            fRec18_perm[j83] = fRec18_tmp[vsize + j83];
        }
        /* Vectorizable loop 65 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec44[i] =
                ((iSlow25) ? fZec26[i] : fSlow24 * fZec27[i] * fSlow41 + fRec10[i] * fSlow42);
        }
        /* Vectorizable loop 66 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec45[i] =
                ((iSlow25) ? fZec37[i] : fSlow24 * fSlow41 * fZec38[i] + fRec18[i] * fSlow42);
        }
        /* Vectorizable loop 67 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec46[i] = fZec44[i] + fZec45[i];
        }
        /* Recursive loop 68 */
        /* Pre code */
        for (int j92 = 0; j92 < 4; j92 = j92 + 1) {
            fRec33_tmp[j92] = fRec33_perm[j92];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec33[i] =
                fZec46[i] - fConst30 * (fConst31 * fRec33[i - 2] + fConst32 * fRec33[i - 1]);
        }
        /* Post code */
        for (int j93 = 0; j93 < 4; j93 = j93 + 1) {
            fRec33_perm[j93] = fRec33_tmp[vsize + j93];
        }
        /* Recursive loop 69 */
        /* Pre code */
        for (int j94 = 0; j94 < 4; j94 = j94 + 1) {
            fRec32_tmp[j94] = fRec32_perm[j94];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec32[i] = fConst30 * (fConst34 * fRec33[i] + fConst35 * fRec33[i - 1] +
                                    fConst34 * fRec33[i - 2]) -
                        fConst36 * (fConst37 * fRec32[i - 2] + fConst38 * fRec32[i - 1]);
        }
        /* Post code */
        for (int j95 = 0; j95 < 4; j95 = j95 + 1) {
            fRec32_perm[j95] = fRec32_tmp[vsize + j95];
        }
        /* Recursive loop 70 */
        /* Pre code */
        for (int j96 = 0; j96 < 4; j96 = j96 + 1) {
            fRec31_tmp[j96] = fRec31_perm[j96];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec31[i] = fConst36 * (fConst39 * fRec32[i] + fConst40 * fRec32[i - 1] +
                                    fConst39 * fRec32[i - 2]) -
                        fConst41 * (fConst42 * fRec31[i - 2] + fConst43 * fRec31[i - 1]);
        }
        /* Post code */
        for (int j97 = 0; j97 < 4; j97 = j97 + 1) {
            fRec31_perm[j97] = fRec31_tmp[vsize + j97];
        }
        /* Vectorizable loop 71 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec47[i] = fConst41 * (fConst44 * fRec31[i] + fConst45 * fRec31[i - 1] +
                                    fConst44 * fRec31[i - 2]);
        }
        /* Recursive loop 72 */
        /* Pre code */
        for (int j106 = 0; j106 < 4; j106 = j106 + 1) {
            fRec40_tmp[j106] = fRec40_perm[j106];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec40[i] =
                fZec47[i] - fConst68 * (fConst69 * fRec40[i - 2] + fConst70 * fRec40[i - 1]);
        }
        /* Post code */
        for (int j107 = 0; j107 < 4; j107 = j107 + 1) {
            fRec40_perm[j107] = fRec40_tmp[vsize + j107];
        }
        /* Recursive loop 73 */
        /* Pre code */
        for (int j108 = 0; j108 < 4; j108 = j108 + 1) {
            fRec39_tmp[j108] = fRec39_perm[j108];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec39[i] = fConst68 * (fConst72 * fRec40[i] + fConst73 * fRec40[i - 1] +
                                    fConst72 * fRec40[i - 2]) -
                        fConst74 * (fConst75 * fRec39[i - 2] + fConst76 * fRec39[i - 1]);
        }
        /* Post code */
        for (int j109 = 0; j109 < 4; j109 = j109 + 1) {
            fRec39_perm[j109] = fRec39_tmp[vsize + j109];
        }
        /* Recursive loop 74 */
        /* Pre code */
        for (int j110 = 0; j110 < 4; j110 = j110 + 1) {
            fRec38_tmp[j110] = fRec38_perm[j110];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec38[i] = fConst74 * (fConst77 * fRec39[i] + fConst78 * fRec39[i - 1] +
                                    fConst77 * fRec39[i - 2]) -
                        fConst79 * (fConst80 * fRec38[i - 2] + fConst81 * fRec38[i - 1]);
        }
        /* Post code */
        for (int j111 = 0; j111 < 4; j111 = j111 + 1) {
            fRec38_perm[j111] = fRec38_tmp[vsize + j111];
        }
        /* Vectorizable loop 75 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec48[i] = fConst79 * (fConst82 * fRec38[i] + fConst83 * fRec38[i - 1] +
                                    fConst82 * fRec38[i - 2]);
        }
        /* Recursive loop 76 */
        /* Pre code */
        for (int j120 = 0; j120 < 4; j120 = j120 + 1) {
            fRec47_tmp[j120] = fRec47_perm[j120];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec47[i] =
                fZec48[i] - fConst106 * (fConst107 * fRec47[i - 2] + fConst108 * fRec47[i - 1]);
        }
        /* Post code */
        for (int j121 = 0; j121 < 4; j121 = j121 + 1) {
            fRec47_perm[j121] = fRec47_tmp[vsize + j121];
        }
        /* Recursive loop 77 */
        /* Pre code */
        for (int j122 = 0; j122 < 4; j122 = j122 + 1) {
            fRec46_tmp[j122] = fRec46_perm[j122];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec46[i] = fConst106 * (fConst110 * fRec47[i] + fConst111 * fRec47[i - 1] +
                                     fConst110 * fRec47[i - 2]) -
                        fConst112 * (fConst113 * fRec46[i - 2] + fConst114 * fRec46[i - 1]);
        }
        /* Post code */
        for (int j123 = 0; j123 < 4; j123 = j123 + 1) {
            fRec46_perm[j123] = fRec46_tmp[vsize + j123];
        }
        /* Recursive loop 78 */
        /* Pre code */
        for (int j124 = 0; j124 < 4; j124 = j124 + 1) {
            fRec45_tmp[j124] = fRec45_perm[j124];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec45[i] = fConst112 * (fConst115 * fRec46[i] + fConst116 * fRec46[i - 1] +
                                     fConst115 * fRec46[i - 2]) -
                        fConst117 * (fConst118 * fRec45[i - 2] + fConst119 * fRec45[i - 1]);
        }
        /* Post code */
        for (int j125 = 0; j125 < 4; j125 = j125 + 1) {
            fRec45_perm[j125] = fRec45_tmp[vsize + j125];
        }
        /* Vectorizable loop 79 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec49[i] = fConst117 * (fConst120 * fRec45[i] + fConst121 * fRec45[i - 1] +
                                     fConst120 * fRec45[i - 2]);
        }
        /* Recursive loop 80 */
        /* Pre code */
        for (int j134 = 0; j134 < 4; j134 = j134 + 1) {
            fRec54_tmp[j134] = fRec54_perm[j134];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec54[i] =
                fZec49[i] - fConst144 * (fConst145 * fRec54[i - 2] + fConst146 * fRec54[i - 1]);
        }
        /* Post code */
        for (int j135 = 0; j135 < 4; j135 = j135 + 1) {
            fRec54_perm[j135] = fRec54_tmp[vsize + j135];
        }
        /* Recursive loop 81 */
        /* Pre code */
        for (int j136 = 0; j136 < 4; j136 = j136 + 1) {
            fRec53_tmp[j136] = fRec53_perm[j136];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec53[i] = fConst144 * (fConst148 * fRec54[i] + fConst149 * fRec54[i - 1] +
                                     fConst148 * fRec54[i - 2]) -
                        fConst150 * (fConst151 * fRec53[i - 2] + fConst152 * fRec53[i - 1]);
        }
        /* Post code */
        for (int j137 = 0; j137 < 4; j137 = j137 + 1) {
            fRec53_perm[j137] = fRec53_tmp[vsize + j137];
        }
        /* Recursive loop 82 */
        /* Pre code */
        for (int j138 = 0; j138 < 4; j138 = j138 + 1) {
            fRec52_tmp[j138] = fRec52_perm[j138];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec52[i] = fConst150 * (fConst153 * fRec53[i] + fConst154 * fRec53[i - 1] +
                                     fConst153 * fRec53[i - 2]) -
                        fConst155 * (fConst156 * fRec52[i - 2] + fConst157 * fRec52[i - 1]);
        }
        /* Post code */
        for (int j139 = 0; j139 < 4; j139 = j139 + 1) {
            fRec52_perm[j139] = fRec52_tmp[vsize + j139];
        }
        /* Vectorizable loop 83 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec50[i] = fConst155 * (fConst158 * fRec52[i] + fConst159 * fRec52[i - 1] +
                                     fConst158 * fRec52[i - 2]);
        }
        /* Recursive loop 84 */
        /* Pre code */
        for (int j148 = 0; j148 < 4; j148 = j148 + 1) {
            fRec61_tmp[j148] = fRec61_perm[j148];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec61[i] =
                fZec50[i] - fConst182 * (fConst183 * fRec61[i - 2] + fConst184 * fRec61[i - 1]);
        }
        /* Post code */
        for (int j149 = 0; j149 < 4; j149 = j149 + 1) {
            fRec61_perm[j149] = fRec61_tmp[vsize + j149];
        }
        /* Recursive loop 85 */
        /* Pre code */
        for (int j150 = 0; j150 < 4; j150 = j150 + 1) {
            fRec60_tmp[j150] = fRec60_perm[j150];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec60[i] = fConst182 * (fConst186 * fRec61[i] + fConst187 * fRec61[i - 1] +
                                     fConst186 * fRec61[i - 2]) -
                        fConst188 * (fConst189 * fRec60[i - 2] + fConst190 * fRec60[i - 1]);
        }
        /* Post code */
        for (int j151 = 0; j151 < 4; j151 = j151 + 1) {
            fRec60_perm[j151] = fRec60_tmp[vsize + j151];
        }
        /* Recursive loop 86 */
        /* Pre code */
        for (int j152 = 0; j152 < 4; j152 = j152 + 1) {
            fRec59_tmp[j152] = fRec59_perm[j152];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec59[i] = fConst188 * (fConst191 * fRec60[i] + fConst192 * fRec60[i - 1] +
                                     fConst191 * fRec60[i - 2]) -
                        fConst193 * (fConst194 * fRec59[i - 2] + fConst195 * fRec59[i - 1]);
        }
        /* Post code */
        for (int j153 = 0; j153 < 4; j153 = j153 + 1) {
            fRec59_perm[j153] = fRec59_tmp[vsize + j153];
        }
        /* Vectorizable loop 87 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec51[i] = fConst193 * (fConst196 * fRec59[i] + fConst197 * fRec59[i - 1] +
                                     fConst196 * fRec59[i - 2]);
        }
        /* Recursive loop 88 */
        /* Pre code */
        for (int j162 = 0; j162 < 4; j162 = j162 + 1) {
            fRec68_tmp[j162] = fRec68_perm[j162];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec68[i] =
                fZec51[i] - fConst220 * (fConst221 * fRec68[i - 2] + fConst222 * fRec68[i - 1]);
        }
        /* Post code */
        for (int j163 = 0; j163 < 4; j163 = j163 + 1) {
            fRec68_perm[j163] = fRec68_tmp[vsize + j163];
        }
        /* Recursive loop 89 */
        /* Pre code */
        for (int j164 = 0; j164 < 4; j164 = j164 + 1) {
            fRec67_tmp[j164] = fRec67_perm[j164];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec67[i] = fConst220 * (fConst224 * fRec68[i] + fConst225 * fRec68[i - 1] +
                                     fConst224 * fRec68[i - 2]) -
                        fConst226 * (fConst227 * fRec67[i - 2] + fConst228 * fRec67[i - 1]);
        }
        /* Post code */
        for (int j165 = 0; j165 < 4; j165 = j165 + 1) {
            fRec67_perm[j165] = fRec67_tmp[vsize + j165];
        }
        /* Recursive loop 90 */
        /* Pre code */
        for (int j166 = 0; j166 < 4; j166 = j166 + 1) {
            fRec66_tmp[j166] = fRec66_perm[j166];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec66[i] = fConst226 * (fConst229 * fRec67[i] + fConst230 * fRec67[i - 1] +
                                     fConst229 * fRec67[i - 2]) -
                        fConst231 * (fConst232 * fRec66[i - 2] + fConst233 * fRec66[i - 1]);
        }
        /* Post code */
        for (int j167 = 0; j167 < 4; j167 = j167 + 1) {
            fRec66_perm[j167] = fRec66_tmp[vsize + j167];
        }
        /* Vectorizable loop 91 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec52[i] = fConst231 * (fConst234 * fRec66[i] + fConst235 * fRec66[i - 1] +
                                     fConst234 * fRec66[i - 2]);
        }
        /* Recursive loop 92 */
        /* Pre code */
        for (int j176 = 0; j176 < 4; j176 = j176 + 1) {
            fRec75_tmp[j176] = fRec75_perm[j176];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec75[i] =
                fZec52[i] - fConst258 * (fConst259 * fRec75[i - 2] + fConst260 * fRec75[i - 1]);
        }
        /* Post code */
        for (int j177 = 0; j177 < 4; j177 = j177 + 1) {
            fRec75_perm[j177] = fRec75_tmp[vsize + j177];
        }
        /* Recursive loop 93 */
        /* Pre code */
        for (int j178 = 0; j178 < 4; j178 = j178 + 1) {
            fRec74_tmp[j178] = fRec74_perm[j178];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec74[i] = fConst258 * (fConst262 * fRec75[i] + fConst263 * fRec75[i - 1] +
                                     fConst262 * fRec75[i - 2]) -
                        fConst264 * (fConst265 * fRec74[i - 2] + fConst266 * fRec74[i - 1]);
        }
        /* Post code */
        for (int j179 = 0; j179 < 4; j179 = j179 + 1) {
            fRec74_perm[j179] = fRec74_tmp[vsize + j179];
        }
        /* Recursive loop 94 */
        /* Pre code */
        for (int j180 = 0; j180 < 4; j180 = j180 + 1) {
            fRec73_tmp[j180] = fRec73_perm[j180];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec73[i] = fConst264 * (fConst267 * fRec74[i] + fConst268 * fRec74[i - 1] +
                                     fConst267 * fRec74[i - 2]) -
                        fConst269 * (fConst270 * fRec73[i - 2] + fConst271 * fRec73[i - 1]);
        }
        /* Post code */
        for (int j181 = 0; j181 < 4; j181 = j181 + 1) {
            fRec73_perm[j181] = fRec73_tmp[vsize + j181];
        }
        /* Vectorizable loop 95 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec53[i] = fConst269 * (fConst272 * fRec73[i] + fConst273 * fRec73[i - 1] +
                                     fConst272 * fRec73[i - 2]);
        }
        /* Recursive loop 96 */
        /* Pre code */
        for (int j190 = 0; j190 < 4; j190 = j190 + 1) {
            fRec82_tmp[j190] = fRec82_perm[j190];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec82[i] =
                fZec53[i] - fConst296 * (fConst297 * fRec82[i - 2] + fConst298 * fRec82[i - 1]);
        }
        /* Post code */
        for (int j191 = 0; j191 < 4; j191 = j191 + 1) {
            fRec82_perm[j191] = fRec82_tmp[vsize + j191];
        }
        /* Recursive loop 97 */
        /* Pre code */
        for (int j192 = 0; j192 < 4; j192 = j192 + 1) {
            fRec81_tmp[j192] = fRec81_perm[j192];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec81[i] = fConst296 * (fConst300 * fRec82[i] + fConst301 * fRec82[i - 1] +
                                     fConst300 * fRec82[i - 2]) -
                        fConst302 * (fConst303 * fRec81[i - 2] + fConst304 * fRec81[i - 1]);
        }
        /* Post code */
        for (int j193 = 0; j193 < 4; j193 = j193 + 1) {
            fRec81_perm[j193] = fRec81_tmp[vsize + j193];
        }
        /* Recursive loop 98 */
        /* Pre code */
        for (int j194 = 0; j194 < 4; j194 = j194 + 1) {
            fRec80_tmp[j194] = fRec80_perm[j194];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec80[i] = fConst302 * (fConst305 * fRec81[i] + fConst306 * fRec81[i - 1] +
                                     fConst305 * fRec81[i - 2]) -
                        fConst307 * (fConst308 * fRec80[i - 2] + fConst309 * fRec80[i - 1]);
        }
        /* Post code */
        for (int j195 = 0; j195 < 4; j195 = j195 + 1) {
            fRec80_perm[j195] = fRec80_tmp[vsize + j195];
        }
        /* Vectorizable loop 99 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec54[i] = fConst307 * (fConst310 * fRec80[i] + fConst311 * fRec80[i - 1] +
                                     fConst310 * fRec80[i - 2]);
        }
        /* Recursive loop 100 */
        /* Pre code */
        for (int j204 = 0; j204 < 4; j204 = j204 + 1) {
            fRec89_tmp[j204] = fRec89_perm[j204];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec89[i] =
                fZec54[i] - fConst334 * (fConst335 * fRec89[i - 2] + fConst336 * fRec89[i - 1]);
        }
        /* Post code */
        for (int j205 = 0; j205 < 4; j205 = j205 + 1) {
            fRec89_perm[j205] = fRec89_tmp[vsize + j205];
        }
        /* Recursive loop 101 */
        /* Pre code */
        for (int j206 = 0; j206 < 4; j206 = j206 + 1) {
            fRec88_tmp[j206] = fRec88_perm[j206];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec88[i] = fConst334 * (fConst338 * fRec89[i] + fConst339 * fRec89[i - 1] +
                                     fConst338 * fRec89[i - 2]) -
                        fConst340 * (fConst341 * fRec88[i - 2] + fConst342 * fRec88[i - 1]);
        }
        /* Post code */
        for (int j207 = 0; j207 < 4; j207 = j207 + 1) {
            fRec88_perm[j207] = fRec88_tmp[vsize + j207];
        }
        /* Recursive loop 102 */
        /* Pre code */
        for (int j208 = 0; j208 < 4; j208 = j208 + 1) {
            fRec87_tmp[j208] = fRec87_perm[j208];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec87[i] = fConst340 * (fConst343 * fRec88[i] + fConst344 * fRec88[i - 1] +
                                     fConst343 * fRec88[i - 2]) -
                        fConst345 * (fConst346 * fRec87[i - 2] + fConst347 * fRec87[i - 1]);
        }
        /* Post code */
        for (int j209 = 0; j209 < 4; j209 = j209 + 1) {
            fRec87_perm[j209] = fRec87_tmp[vsize + j209];
        }
        /* Vectorizable loop 103 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec55[i] = fConst345 * (fConst348 * fRec87[i] + fConst349 * fRec87[i - 1] +
                                     fConst348 * fRec87[i - 2]);
        }
        /* Recursive loop 104 */
        /* Pre code */
        for (int j218 = 0; j218 < 4; j218 = j218 + 1) {
            fRec96_tmp[j218] = fRec96_perm[j218];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec96[i] =
                fZec55[i] - fConst372 * (fConst373 * fRec96[i - 2] + fConst374 * fRec96[i - 1]);
        }
        /* Post code */
        for (int j219 = 0; j219 < 4; j219 = j219 + 1) {
            fRec96_perm[j219] = fRec96_tmp[vsize + j219];
        }
        /* Recursive loop 105 */
        /* Pre code */
        for (int j220 = 0; j220 < 4; j220 = j220 + 1) {
            fRec95_tmp[j220] = fRec95_perm[j220];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec95[i] = fConst372 * (fConst376 * fRec96[i] + fConst377 * fRec96[i - 1] +
                                     fConst376 * fRec96[i - 2]) -
                        fConst378 * (fConst379 * fRec95[i - 2] + fConst380 * fRec95[i - 1]);
        }
        /* Post code */
        for (int j221 = 0; j221 < 4; j221 = j221 + 1) {
            fRec95_perm[j221] = fRec95_tmp[vsize + j221];
        }
        /* Recursive loop 106 */
        /* Pre code */
        for (int j222 = 0; j222 < 4; j222 = j222 + 1) {
            fRec94_tmp[j222] = fRec94_perm[j222];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec94[i] = fConst378 * (fConst381 * fRec95[i] + fConst382 * fRec95[i - 1] +
                                     fConst381 * fRec95[i - 2]) -
                        fConst383 * (fConst384 * fRec94[i - 2] + fConst385 * fRec94[i - 1]);
        }
        /* Post code */
        for (int j223 = 0; j223 < 4; j223 = j223 + 1) {
            fRec94_perm[j223] = fRec94_tmp[vsize + j223];
        }
        /* Vectorizable loop 107 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec56[i] = fConst383 * (fConst386 * fRec94[i] + fConst387 * fRec94[i - 1] +
                                     fConst386 * fRec94[i - 2]);
        }
        /* Recursive loop 108 */
        /* Pre code */
        for (int j232 = 0; j232 < 4; j232 = j232 + 1) {
            fRec103_tmp[j232] = fRec103_perm[j232];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec103[i] =
                fZec56[i] - fConst410 * (fConst411 * fRec103[i - 2] + fConst412 * fRec103[i - 1]);
        }
        /* Post code */
        for (int j233 = 0; j233 < 4; j233 = j233 + 1) {
            fRec103_perm[j233] = fRec103_tmp[vsize + j233];
        }
        /* Recursive loop 109 */
        /* Pre code */
        for (int j234 = 0; j234 < 4; j234 = j234 + 1) {
            fRec102_tmp[j234] = fRec102_perm[j234];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec102[i] = fConst410 * (fConst414 * fRec103[i] + fConst415 * fRec103[i - 1] +
                                      fConst414 * fRec103[i - 2]) -
                         fConst416 * (fConst417 * fRec102[i - 2] + fConst418 * fRec102[i - 1]);
        }
        /* Post code */
        for (int j235 = 0; j235 < 4; j235 = j235 + 1) {
            fRec102_perm[j235] = fRec102_tmp[vsize + j235];
        }
        /* Recursive loop 110 */
        /* Pre code */
        for (int j236 = 0; j236 < 4; j236 = j236 + 1) {
            fRec101_tmp[j236] = fRec101_perm[j236];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec101[i] = fConst416 * (fConst419 * fRec102[i] + fConst420 * fRec102[i - 1] +
                                      fConst419 * fRec102[i - 2]) -
                         fConst421 * (fConst422 * fRec101[i - 2] + fConst423 * fRec101[i - 1]);
        }
        /* Post code */
        for (int j237 = 0; j237 < 4; j237 = j237 + 1) {
            fRec101_perm[j237] = fRec101_tmp[vsize + j237];
        }
        /* Vectorizable loop 111 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec57[i] = fConst421 * (fConst424 * fRec101[i] + fConst425 * fRec101[i - 1] +
                                     fConst424 * fRec101[i - 2]);
        }
        /* Recursive loop 112 */
        /* Pre code */
        for (int j246 = 0; j246 < 4; j246 = j246 + 1) {
            fRec110_tmp[j246] = fRec110_perm[j246];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec110[i] =
                fZec57[i] - fConst448 * (fConst449 * fRec110[i - 2] + fConst450 * fRec110[i - 1]);
        }
        /* Post code */
        for (int j247 = 0; j247 < 4; j247 = j247 + 1) {
            fRec110_perm[j247] = fRec110_tmp[vsize + j247];
        }
        /* Recursive loop 113 */
        /* Pre code */
        for (int j248 = 0; j248 < 4; j248 = j248 + 1) {
            fRec109_tmp[j248] = fRec109_perm[j248];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec109[i] = fConst448 * (fConst452 * fRec110[i] + fConst453 * fRec110[i - 1] +
                                      fConst452 * fRec110[i - 2]) -
                         fConst454 * (fConst455 * fRec109[i - 2] + fConst456 * fRec109[i - 1]);
        }
        /* Post code */
        for (int j249 = 0; j249 < 4; j249 = j249 + 1) {
            fRec109_perm[j249] = fRec109_tmp[vsize + j249];
        }
        /* Recursive loop 114 */
        /* Pre code */
        for (int j250 = 0; j250 < 4; j250 = j250 + 1) {
            fRec108_tmp[j250] = fRec108_perm[j250];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec108[i] = fConst454 * (fConst457 * fRec109[i] + fConst458 * fRec109[i - 1] +
                                      fConst457 * fRec109[i - 2]) -
                         fConst459 * (fConst460 * fRec108[i - 2] + fConst461 * fRec108[i - 1]);
        }
        /* Post code */
        for (int j251 = 0; j251 < 4; j251 = j251 + 1) {
            fRec108_perm[j251] = fRec108_tmp[vsize + j251];
        }
        /* Vectorizable loop 115 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec58[i] = fConst459 * (fConst462 * fRec108[i] + fConst463 * fRec108[i - 1] +
                                     fConst462 * fRec108[i - 2]);
        }
        /* Recursive loop 116 */
        /* Pre code */
        for (int j260 = 0; j260 < 4; j260 = j260 + 1) {
            fRec117_tmp[j260] = fRec117_perm[j260];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec117[i] =
                fZec58[i] - fConst486 * (fConst487 * fRec117[i - 2] + fConst488 * fRec117[i - 1]);
        }
        /* Post code */
        for (int j261 = 0; j261 < 4; j261 = j261 + 1) {
            fRec117_perm[j261] = fRec117_tmp[vsize + j261];
        }
        /* Recursive loop 117 */
        /* Pre code */
        for (int j262 = 0; j262 < 4; j262 = j262 + 1) {
            fRec116_tmp[j262] = fRec116_perm[j262];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec116[i] = fConst486 * (fConst490 * fRec117[i] + fConst491 * fRec117[i - 1] +
                                      fConst490 * fRec117[i - 2]) -
                         fConst492 * (fConst493 * fRec116[i - 2] + fConst494 * fRec116[i - 1]);
        }
        /* Post code */
        for (int j263 = 0; j263 < 4; j263 = j263 + 1) {
            fRec116_perm[j263] = fRec116_tmp[vsize + j263];
        }
        /* Recursive loop 118 */
        /* Pre code */
        for (int j264 = 0; j264 < 4; j264 = j264 + 1) {
            fRec115_tmp[j264] = fRec115_perm[j264];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec115[i] = fConst492 * (fConst495 * fRec116[i] + fConst496 * fRec116[i - 1] +
                                      fConst495 * fRec116[i - 2]) -
                         fConst497 * (fConst498 * fRec115[i - 2] + fConst499 * fRec115[i - 1]);
        }
        /* Post code */
        for (int j265 = 0; j265 < 4; j265 = j265 + 1) {
            fRec115_perm[j265] = fRec115_tmp[vsize + j265];
        }
        /* Vectorizable loop 119 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec59[i] = fConst497 * (fConst500 * fRec115[i] + fConst501 * fRec115[i - 1] +
                                     fConst500 * fRec115[i - 2]);
        }
        /* Recursive loop 120 */
        /* Pre code */
        for (int j84 = 0; j84 < 4; j84 = j84 + 1) {
            fRec26_tmp[j84] = fRec26_perm[j84];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec26[i] = fZec46[i] - fConst9 * (fConst10 * fRec26[i - 2] + fConst13 * fRec26[i - 1]);
        }
        /* Post code */
        for (int j85 = 0; j85 < 4; j85 = j85 + 1) {
            fRec26_perm[j85] = fRec26_tmp[vsize + j85];
        }
        /* Recursive loop 121 */
        /* Pre code */
        for (int j98 = 0; j98 < 4; j98 = j98 + 1) {
            fRec30_tmp[j98] = fRec30_perm[j98];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec30[i] =
                fZec47[i] - fConst48 * (fConst49 * fRec30[i - 2] + fConst52 * fRec30[i - 1]);
        }
        /* Post code */
        for (int j99 = 0; j99 < 4; j99 = j99 + 1) {
            fRec30_perm[j99] = fRec30_tmp[vsize + j99];
        }
        /* Recursive loop 122 */
        /* Pre code */
        for (int j112 = 0; j112 < 4; j112 = j112 + 1) {
            fRec37_tmp[j112] = fRec37_perm[j112];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec37[i] =
                fZec48[i] - fConst86 * (fConst87 * fRec37[i - 2] + fConst90 * fRec37[i - 1]);
        }
        /* Post code */
        for (int j113 = 0; j113 < 4; j113 = j113 + 1) {
            fRec37_perm[j113] = fRec37_tmp[vsize + j113];
        }
        /* Recursive loop 123 */
        /* Pre code */
        for (int j126 = 0; j126 < 4; j126 = j126 + 1) {
            fRec44_tmp[j126] = fRec44_perm[j126];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec44[i] =
                fZec49[i] - fConst124 * (fConst125 * fRec44[i - 2] + fConst128 * fRec44[i - 1]);
        }
        /* Post code */
        for (int j127 = 0; j127 < 4; j127 = j127 + 1) {
            fRec44_perm[j127] = fRec44_tmp[vsize + j127];
        }
        /* Recursive loop 124 */
        /* Pre code */
        for (int j140 = 0; j140 < 4; j140 = j140 + 1) {
            fRec51_tmp[j140] = fRec51_perm[j140];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec51[i] =
                fZec50[i] - fConst162 * (fConst163 * fRec51[i - 2] + fConst166 * fRec51[i - 1]);
        }
        /* Post code */
        for (int j141 = 0; j141 < 4; j141 = j141 + 1) {
            fRec51_perm[j141] = fRec51_tmp[vsize + j141];
        }
        /* Recursive loop 125 */
        /* Pre code */
        for (int j154 = 0; j154 < 4; j154 = j154 + 1) {
            fRec58_tmp[j154] = fRec58_perm[j154];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec58[i] =
                fZec51[i] - fConst200 * (fConst201 * fRec58[i - 2] + fConst204 * fRec58[i - 1]);
        }
        /* Post code */
        for (int j155 = 0; j155 < 4; j155 = j155 + 1) {
            fRec58_perm[j155] = fRec58_tmp[vsize + j155];
        }
        /* Recursive loop 126 */
        /* Pre code */
        for (int j168 = 0; j168 < 4; j168 = j168 + 1) {
            fRec65_tmp[j168] = fRec65_perm[j168];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec65[i] =
                fZec52[i] - fConst238 * (fConst239 * fRec65[i - 2] + fConst242 * fRec65[i - 1]);
        }
        /* Post code */
        for (int j169 = 0; j169 < 4; j169 = j169 + 1) {
            fRec65_perm[j169] = fRec65_tmp[vsize + j169];
        }
        /* Recursive loop 127 */
        /* Pre code */
        for (int j182 = 0; j182 < 4; j182 = j182 + 1) {
            fRec72_tmp[j182] = fRec72_perm[j182];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec72[i] =
                fZec53[i] - fConst276 * (fConst277 * fRec72[i - 2] + fConst280 * fRec72[i - 1]);
        }
        /* Post code */
        for (int j183 = 0; j183 < 4; j183 = j183 + 1) {
            fRec72_perm[j183] = fRec72_tmp[vsize + j183];
        }
        /* Recursive loop 128 */
        /* Pre code */
        for (int j196 = 0; j196 < 4; j196 = j196 + 1) {
            fRec79_tmp[j196] = fRec79_perm[j196];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec79[i] =
                fZec54[i] - fConst314 * (fConst315 * fRec79[i - 2] + fConst318 * fRec79[i - 1]);
        }
        /* Post code */
        for (int j197 = 0; j197 < 4; j197 = j197 + 1) {
            fRec79_perm[j197] = fRec79_tmp[vsize + j197];
        }
        /* Recursive loop 129 */
        /* Pre code */
        for (int j210 = 0; j210 < 4; j210 = j210 + 1) {
            fRec86_tmp[j210] = fRec86_perm[j210];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec86[i] =
                fZec55[i] - fConst352 * (fConst353 * fRec86[i - 2] + fConst356 * fRec86[i - 1]);
        }
        /* Post code */
        for (int j211 = 0; j211 < 4; j211 = j211 + 1) {
            fRec86_perm[j211] = fRec86_tmp[vsize + j211];
        }
        /* Recursive loop 130 */
        /* Pre code */
        for (int j224 = 0; j224 < 4; j224 = j224 + 1) {
            fRec93_tmp[j224] = fRec93_perm[j224];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec93[i] =
                fZec56[i] - fConst390 * (fConst391 * fRec93[i - 2] + fConst394 * fRec93[i - 1]);
        }
        /* Post code */
        for (int j225 = 0; j225 < 4; j225 = j225 + 1) {
            fRec93_perm[j225] = fRec93_tmp[vsize + j225];
        }
        /* Recursive loop 131 */
        /* Pre code */
        for (int j238 = 0; j238 < 4; j238 = j238 + 1) {
            fRec100_tmp[j238] = fRec100_perm[j238];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec100[i] =
                fZec57[i] - fConst428 * (fConst429 * fRec100[i - 2] + fConst432 * fRec100[i - 1]);
        }
        /* Post code */
        for (int j239 = 0; j239 < 4; j239 = j239 + 1) {
            fRec100_perm[j239] = fRec100_tmp[vsize + j239];
        }
        /* Recursive loop 132 */
        /* Pre code */
        for (int j252 = 0; j252 < 4; j252 = j252 + 1) {
            fRec107_tmp[j252] = fRec107_perm[j252];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec107[i] =
                fZec58[i] - fConst466 * (fConst467 * fRec107[i - 2] + fConst470 * fRec107[i - 1]);
        }
        /* Post code */
        for (int j253 = 0; j253 < 4; j253 = j253 + 1) {
            fRec107_perm[j253] = fRec107_tmp[vsize + j253];
        }
        /* Recursive loop 133 */
        /* Pre code */
        for (int j266 = 0; j266 < 4; j266 = j266 + 1) {
            fRec114_tmp[j266] = fRec114_perm[j266];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec114[i] =
                fZec59[i] - fConst504 * (fConst505 * fRec114[i - 2] + fConst508 * fRec114[i - 1]);
        }
        /* Post code */
        for (int j267 = 0; j267 < 4; j267 = j267 + 1) {
            fRec114_perm[j267] = fRec114_tmp[vsize + j267];
        }
        /* Recursive loop 134 */
        /* Pre code */
        for (int j274 = 0; j274 < 4; j274 = j274 + 1) {
            fRec121_tmp[j274] = fRec121_perm[j274];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec121[i] =
                fZec59[i] - fConst524 * (fConst525 * fRec121[i - 2] + fConst526 * fRec121[i - 1]);
        }
        /* Post code */
        for (int j275 = 0; j275 < 4; j275 = j275 + 1) {
            fRec121_perm[j275] = fRec121_tmp[vsize + j275];
        }
        /* Recursive loop 135 */
        /* Pre code */
        for (int j86 = 0; j86 < 4; j86 = j86 + 1) {
            fRec25_tmp[j86] = fRec25_perm[j86];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec25[i] = fConst9 * (fConst15 * fRec26[i] + fConst16 * fRec26[i - 1] +
                                   fConst15 * fRec26[i - 2]) -
                        fConst17 * (fConst18 * fRec25[i - 2] + fConst19 * fRec25[i - 1]);
        }
        /* Post code */
        for (int j87 = 0; j87 < 4; j87 = j87 + 1) {
            fRec25_perm[j87] = fRec25_tmp[vsize + j87];
        }
        /* Recursive loop 136 */
        /* Pre code */
        for (int j100 = 0; j100 < 4; j100 = j100 + 1) {
            fRec29_tmp[j100] = fRec29_perm[j100];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec29[i] = fConst48 * (fConst54 * fRec30[i] + fConst55 * fRec30[i - 1] +
                                    fConst54 * fRec30[i - 2]) -
                        fConst56 * (fConst57 * fRec29[i - 2] + fConst58 * fRec29[i - 1]);
        }
        /* Post code */
        for (int j101 = 0; j101 < 4; j101 = j101 + 1) {
            fRec29_perm[j101] = fRec29_tmp[vsize + j101];
        }
        /* Recursive loop 137 */
        /* Pre code */
        for (int j114 = 0; j114 < 4; j114 = j114 + 1) {
            fRec36_tmp[j114] = fRec36_perm[j114];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec36[i] = fConst86 * (fConst92 * fRec37[i] + fConst93 * fRec37[i - 1] +
                                    fConst92 * fRec37[i - 2]) -
                        fConst94 * (fConst95 * fRec36[i - 2] + fConst96 * fRec36[i - 1]);
        }
        /* Post code */
        for (int j115 = 0; j115 < 4; j115 = j115 + 1) {
            fRec36_perm[j115] = fRec36_tmp[vsize + j115];
        }
        /* Recursive loop 138 */
        /* Pre code */
        for (int j128 = 0; j128 < 4; j128 = j128 + 1) {
            fRec43_tmp[j128] = fRec43_perm[j128];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec43[i] = fConst124 * (fConst130 * fRec44[i] + fConst131 * fRec44[i - 1] +
                                     fConst130 * fRec44[i - 2]) -
                        fConst132 * (fConst133 * fRec43[i - 2] + fConst134 * fRec43[i - 1]);
        }
        /* Post code */
        for (int j129 = 0; j129 < 4; j129 = j129 + 1) {
            fRec43_perm[j129] = fRec43_tmp[vsize + j129];
        }
        /* Recursive loop 139 */
        /* Pre code */
        for (int j142 = 0; j142 < 4; j142 = j142 + 1) {
            fRec50_tmp[j142] = fRec50_perm[j142];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec50[i] = fConst162 * (fConst168 * fRec51[i] + fConst169 * fRec51[i - 1] +
                                     fConst168 * fRec51[i - 2]) -
                        fConst170 * (fConst171 * fRec50[i - 2] + fConst172 * fRec50[i - 1]);
        }
        /* Post code */
        for (int j143 = 0; j143 < 4; j143 = j143 + 1) {
            fRec50_perm[j143] = fRec50_tmp[vsize + j143];
        }
        /* Recursive loop 140 */
        /* Pre code */
        for (int j156 = 0; j156 < 4; j156 = j156 + 1) {
            fRec57_tmp[j156] = fRec57_perm[j156];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec57[i] = fConst200 * (fConst206 * fRec58[i] + fConst207 * fRec58[i - 1] +
                                     fConst206 * fRec58[i - 2]) -
                        fConst208 * (fConst209 * fRec57[i - 2] + fConst210 * fRec57[i - 1]);
        }
        /* Post code */
        for (int j157 = 0; j157 < 4; j157 = j157 + 1) {
            fRec57_perm[j157] = fRec57_tmp[vsize + j157];
        }
        /* Recursive loop 141 */
        /* Pre code */
        for (int j170 = 0; j170 < 4; j170 = j170 + 1) {
            fRec64_tmp[j170] = fRec64_perm[j170];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec64[i] = fConst238 * (fConst244 * fRec65[i] + fConst245 * fRec65[i - 1] +
                                     fConst244 * fRec65[i - 2]) -
                        fConst246 * (fConst247 * fRec64[i - 2] + fConst248 * fRec64[i - 1]);
        }
        /* Post code */
        for (int j171 = 0; j171 < 4; j171 = j171 + 1) {
            fRec64_perm[j171] = fRec64_tmp[vsize + j171];
        }
        /* Recursive loop 142 */
        /* Pre code */
        for (int j184 = 0; j184 < 4; j184 = j184 + 1) {
            fRec71_tmp[j184] = fRec71_perm[j184];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec71[i] = fConst276 * (fConst282 * fRec72[i] + fConst283 * fRec72[i - 1] +
                                     fConst282 * fRec72[i - 2]) -
                        fConst284 * (fConst285 * fRec71[i - 2] + fConst286 * fRec71[i - 1]);
        }
        /* Post code */
        for (int j185 = 0; j185 < 4; j185 = j185 + 1) {
            fRec71_perm[j185] = fRec71_tmp[vsize + j185];
        }
        /* Recursive loop 143 */
        /* Pre code */
        for (int j198 = 0; j198 < 4; j198 = j198 + 1) {
            fRec78_tmp[j198] = fRec78_perm[j198];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec78[i] = fConst314 * (fConst320 * fRec79[i] + fConst321 * fRec79[i - 1] +
                                     fConst320 * fRec79[i - 2]) -
                        fConst322 * (fConst323 * fRec78[i - 2] + fConst324 * fRec78[i - 1]);
        }
        /* Post code */
        for (int j199 = 0; j199 < 4; j199 = j199 + 1) {
            fRec78_perm[j199] = fRec78_tmp[vsize + j199];
        }
        /* Recursive loop 144 */
        /* Pre code */
        for (int j212 = 0; j212 < 4; j212 = j212 + 1) {
            fRec85_tmp[j212] = fRec85_perm[j212];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec85[i] = fConst352 * (fConst358 * fRec86[i] + fConst359 * fRec86[i - 1] +
                                     fConst358 * fRec86[i - 2]) -
                        fConst360 * (fConst361 * fRec85[i - 2] + fConst362 * fRec85[i - 1]);
        }
        /* Post code */
        for (int j213 = 0; j213 < 4; j213 = j213 + 1) {
            fRec85_perm[j213] = fRec85_tmp[vsize + j213];
        }
        /* Recursive loop 145 */
        /* Pre code */
        for (int j226 = 0; j226 < 4; j226 = j226 + 1) {
            fRec92_tmp[j226] = fRec92_perm[j226];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec92[i] = fConst390 * (fConst396 * fRec93[i] + fConst397 * fRec93[i - 1] +
                                     fConst396 * fRec93[i - 2]) -
                        fConst398 * (fConst399 * fRec92[i - 2] + fConst400 * fRec92[i - 1]);
        }
        /* Post code */
        for (int j227 = 0; j227 < 4; j227 = j227 + 1) {
            fRec92_perm[j227] = fRec92_tmp[vsize + j227];
        }
        /* Recursive loop 146 */
        /* Pre code */
        for (int j240 = 0; j240 < 4; j240 = j240 + 1) {
            fRec99_tmp[j240] = fRec99_perm[j240];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec99[i] = fConst428 * (fConst434 * fRec100[i] + fConst435 * fRec100[i - 1] +
                                     fConst434 * fRec100[i - 2]) -
                        fConst436 * (fConst437 * fRec99[i - 2] + fConst438 * fRec99[i - 1]);
        }
        /* Post code */
        for (int j241 = 0; j241 < 4; j241 = j241 + 1) {
            fRec99_perm[j241] = fRec99_tmp[vsize + j241];
        }
        /* Recursive loop 147 */
        /* Pre code */
        for (int j254 = 0; j254 < 4; j254 = j254 + 1) {
            fRec106_tmp[j254] = fRec106_perm[j254];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec106[i] = fConst466 * (fConst472 * fRec107[i] + fConst473 * fRec107[i - 1] +
                                      fConst472 * fRec107[i - 2]) -
                         fConst474 * (fConst475 * fRec106[i - 2] + fConst476 * fRec106[i - 1]);
        }
        /* Post code */
        for (int j255 = 0; j255 < 4; j255 = j255 + 1) {
            fRec106_perm[j255] = fRec106_tmp[vsize + j255];
        }
        /* Recursive loop 148 */
        /* Pre code */
        for (int j268 = 0; j268 < 4; j268 = j268 + 1) {
            fRec113_tmp[j268] = fRec113_perm[j268];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec113[i] = fConst504 * (fConst510 * fRec114[i] + fConst511 * fRec114[i - 1] +
                                      fConst510 * fRec114[i - 2]) -
                         fConst512 * (fConst513 * fRec113[i - 2] + fConst514 * fRec113[i - 1]);
        }
        /* Post code */
        for (int j269 = 0; j269 < 4; j269 = j269 + 1) {
            fRec113_perm[j269] = fRec113_tmp[vsize + j269];
        }
        /* Recursive loop 149 */
        /* Pre code */
        for (int j276 = 0; j276 < 4; j276 = j276 + 1) {
            fRec120_tmp[j276] = fRec120_perm[j276];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec120[i] = fConst524 * (fConst528 * fRec121[i] + fConst529 * fRec121[i - 1] +
                                      fConst528 * fRec121[i - 2]) -
                         fConst530 * (fConst531 * fRec120[i - 2] + fConst532 * fRec120[i - 1]);
        }
        /* Post code */
        for (int j277 = 0; j277 < 4; j277 = j277 + 1) {
            fRec120_perm[j277] = fRec120_tmp[vsize + j277];
        }
        /* Recursive loop 150 */
        /* Pre code */
        for (int j88 = 0; j88 < 4; j88 = j88 + 1) {
            fRec24_tmp[j88] = fRec24_perm[j88];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec24[i] = fConst17 * (fConst21 * fRec25[i] + fConst22 * fRec25[i - 1] +
                                    fConst21 * fRec25[i - 2]) -
                        fConst23 * (fConst24 * fRec24[i - 2] + fConst25 * fRec24[i - 1]);
        }
        /* Post code */
        for (int j89 = 0; j89 < 4; j89 = j89 + 1) {
            fRec24_perm[j89] = fRec24_tmp[vsize + j89];
        }
        /* Recursive loop 151 */
        /* Pre code */
        for (int j102 = 0; j102 < 4; j102 = j102 + 1) {
            fRec28_tmp[j102] = fRec28_perm[j102];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec28[i] = fConst56 * (fConst60 * fRec29[i] + fConst61 * fRec29[i - 1] +
                                    fConst60 * fRec29[i - 2]) -
                        fConst62 * (fConst63 * fRec28[i - 2] + fConst64 * fRec28[i - 1]);
        }
        /* Post code */
        for (int j103 = 0; j103 < 4; j103 = j103 + 1) {
            fRec28_perm[j103] = fRec28_tmp[vsize + j103];
        }
        /* Recursive loop 152 */
        /* Pre code */
        for (int j116 = 0; j116 < 4; j116 = j116 + 1) {
            fRec35_tmp[j116] = fRec35_perm[j116];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec35[i] = fConst94 * (fConst98 * fRec36[i] + fConst99 * fRec36[i - 1] +
                                    fConst98 * fRec36[i - 2]) -
                        fConst100 * (fConst101 * fRec35[i - 2] + fConst102 * fRec35[i - 1]);
        }
        /* Post code */
        for (int j117 = 0; j117 < 4; j117 = j117 + 1) {
            fRec35_perm[j117] = fRec35_tmp[vsize + j117];
        }
        /* Recursive loop 153 */
        /* Pre code */
        for (int j130 = 0; j130 < 4; j130 = j130 + 1) {
            fRec42_tmp[j130] = fRec42_perm[j130];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec42[i] = fConst132 * (fConst136 * fRec43[i] + fConst137 * fRec43[i - 1] +
                                     fConst136 * fRec43[i - 2]) -
                        fConst138 * (fConst139 * fRec42[i - 2] + fConst140 * fRec42[i - 1]);
        }
        /* Post code */
        for (int j131 = 0; j131 < 4; j131 = j131 + 1) {
            fRec42_perm[j131] = fRec42_tmp[vsize + j131];
        }
        /* Recursive loop 154 */
        /* Pre code */
        for (int j144 = 0; j144 < 4; j144 = j144 + 1) {
            fRec49_tmp[j144] = fRec49_perm[j144];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec49[i] = fConst170 * (fConst174 * fRec50[i] + fConst175 * fRec50[i - 1] +
                                     fConst174 * fRec50[i - 2]) -
                        fConst176 * (fConst177 * fRec49[i - 2] + fConst178 * fRec49[i - 1]);
        }
        /* Post code */
        for (int j145 = 0; j145 < 4; j145 = j145 + 1) {
            fRec49_perm[j145] = fRec49_tmp[vsize + j145];
        }
        /* Recursive loop 155 */
        /* Pre code */
        for (int j158 = 0; j158 < 4; j158 = j158 + 1) {
            fRec56_tmp[j158] = fRec56_perm[j158];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec56[i] = fConst208 * (fConst212 * fRec57[i] + fConst213 * fRec57[i - 1] +
                                     fConst212 * fRec57[i - 2]) -
                        fConst214 * (fConst215 * fRec56[i - 2] + fConst216 * fRec56[i - 1]);
        }
        /* Post code */
        for (int j159 = 0; j159 < 4; j159 = j159 + 1) {
            fRec56_perm[j159] = fRec56_tmp[vsize + j159];
        }
        /* Recursive loop 156 */
        /* Pre code */
        for (int j172 = 0; j172 < 4; j172 = j172 + 1) {
            fRec63_tmp[j172] = fRec63_perm[j172];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec63[i] = fConst246 * (fConst250 * fRec64[i] + fConst251 * fRec64[i - 1] +
                                     fConst250 * fRec64[i - 2]) -
                        fConst252 * (fConst253 * fRec63[i - 2] + fConst254 * fRec63[i - 1]);
        }
        /* Post code */
        for (int j173 = 0; j173 < 4; j173 = j173 + 1) {
            fRec63_perm[j173] = fRec63_tmp[vsize + j173];
        }
        /* Recursive loop 157 */
        /* Pre code */
        for (int j186 = 0; j186 < 4; j186 = j186 + 1) {
            fRec70_tmp[j186] = fRec70_perm[j186];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec70[i] = fConst284 * (fConst288 * fRec71[i] + fConst289 * fRec71[i - 1] +
                                     fConst288 * fRec71[i - 2]) -
                        fConst290 * (fConst291 * fRec70[i - 2] + fConst292 * fRec70[i - 1]);
        }
        /* Post code */
        for (int j187 = 0; j187 < 4; j187 = j187 + 1) {
            fRec70_perm[j187] = fRec70_tmp[vsize + j187];
        }
        /* Recursive loop 158 */
        /* Pre code */
        for (int j200 = 0; j200 < 4; j200 = j200 + 1) {
            fRec77_tmp[j200] = fRec77_perm[j200];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec77[i] = fConst322 * (fConst326 * fRec78[i] + fConst327 * fRec78[i - 1] +
                                     fConst326 * fRec78[i - 2]) -
                        fConst328 * (fConst329 * fRec77[i - 2] + fConst330 * fRec77[i - 1]);
        }
        /* Post code */
        for (int j201 = 0; j201 < 4; j201 = j201 + 1) {
            fRec77_perm[j201] = fRec77_tmp[vsize + j201];
        }
        /* Recursive loop 159 */
        /* Pre code */
        for (int j214 = 0; j214 < 4; j214 = j214 + 1) {
            fRec84_tmp[j214] = fRec84_perm[j214];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec84[i] = fConst360 * (fConst364 * fRec85[i] + fConst365 * fRec85[i - 1] +
                                     fConst364 * fRec85[i - 2]) -
                        fConst366 * (fConst367 * fRec84[i - 2] + fConst368 * fRec84[i - 1]);
        }
        /* Post code */
        for (int j215 = 0; j215 < 4; j215 = j215 + 1) {
            fRec84_perm[j215] = fRec84_tmp[vsize + j215];
        }
        /* Recursive loop 160 */
        /* Pre code */
        for (int j228 = 0; j228 < 4; j228 = j228 + 1) {
            fRec91_tmp[j228] = fRec91_perm[j228];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec91[i] = fConst398 * (fConst402 * fRec92[i] + fConst403 * fRec92[i - 1] +
                                     fConst402 * fRec92[i - 2]) -
                        fConst404 * (fConst405 * fRec91[i - 2] + fConst406 * fRec91[i - 1]);
        }
        /* Post code */
        for (int j229 = 0; j229 < 4; j229 = j229 + 1) {
            fRec91_perm[j229] = fRec91_tmp[vsize + j229];
        }
        /* Recursive loop 161 */
        /* Pre code */
        for (int j242 = 0; j242 < 4; j242 = j242 + 1) {
            fRec98_tmp[j242] = fRec98_perm[j242];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec98[i] = fConst436 * (fConst440 * fRec99[i] + fConst441 * fRec99[i - 1] +
                                     fConst440 * fRec99[i - 2]) -
                        fConst442 * (fConst443 * fRec98[i - 2] + fConst444 * fRec98[i - 1]);
        }
        /* Post code */
        for (int j243 = 0; j243 < 4; j243 = j243 + 1) {
            fRec98_perm[j243] = fRec98_tmp[vsize + j243];
        }
        /* Recursive loop 162 */
        /* Pre code */
        for (int j256 = 0; j256 < 4; j256 = j256 + 1) {
            fRec105_tmp[j256] = fRec105_perm[j256];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec105[i] = fConst474 * (fConst478 * fRec106[i] + fConst479 * fRec106[i - 1] +
                                      fConst478 * fRec106[i - 2]) -
                         fConst480 * (fConst481 * fRec105[i - 2] + fConst482 * fRec105[i - 1]);
        }
        /* Post code */
        for (int j257 = 0; j257 < 4; j257 = j257 + 1) {
            fRec105_perm[j257] = fRec105_tmp[vsize + j257];
        }
        /* Recursive loop 163 */
        /* Pre code */
        for (int j270 = 0; j270 < 4; j270 = j270 + 1) {
            fRec112_tmp[j270] = fRec112_perm[j270];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec112[i] = fConst512 * (fConst516 * fRec113[i] + fConst517 * fRec113[i - 1] +
                                      fConst516 * fRec113[i - 2]) -
                         fConst518 * (fConst519 * fRec112[i - 2] + fConst520 * fRec112[i - 1]);
        }
        /* Post code */
        for (int j271 = 0; j271 < 4; j271 = j271 + 1) {
            fRec112_perm[j271] = fRec112_tmp[vsize + j271];
        }
        /* Recursive loop 164 */
        /* Pre code */
        for (int j278 = 0; j278 < 4; j278 = j278 + 1) {
            fRec119_tmp[j278] = fRec119_perm[j278];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec119[i] = fConst530 * (fConst533 * fRec120[i] + fConst534 * fRec120[i - 1] +
                                      fConst533 * fRec120[i - 2]) -
                         fConst535 * (fConst536 * fRec119[i - 2] + fConst537 * fRec119[i - 1]);
        }
        /* Post code */
        for (int j279 = 0; j279 < 4; j279 = j279 + 1) {
            fRec119_perm[j279] = fRec119_tmp[vsize + j279];
        }
        /* Recursive loop 165 */
        /* Pre code */
        for (int j90 = 0; j90 < 4; j90 = j90 + 1) {
            fRec23_tmp[j90] = fRec23_perm[j90];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec23[i] = fRec23[i - 1] * fSlow44 +
                        std::fabs(fConst23 * (fConst28 * fRec24[i] + fConst29 * fRec24[i - 1] +
                                              fConst28 * fRec24[i - 2])) *
                            fSlow45;
        }
        /* Post code */
        for (int j91 = 0; j91 < 4; j91 = j91 + 1) {
            fRec23_perm[j91] = fRec23_tmp[vsize + j91];
        }
        /* Recursive loop 166 */
        /* Pre code */
        for (int j104 = 0; j104 < 4; j104 = j104 + 1) {
            fRec27_tmp[j104] = fRec27_perm[j104];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec27[i] =
                fSlow44 * fRec27[i - 1] +
                fSlow45 * std::fabs(fConst62 * (fConst66 * fRec28[i] + fConst67 * fRec28[i - 1] +
                                                fConst66 * fRec28[i - 2]));
        }
        /* Post code */
        for (int j105 = 0; j105 < 4; j105 = j105 + 1) {
            fRec27_perm[j105] = fRec27_tmp[vsize + j105];
        }
        /* Recursive loop 167 */
        /* Pre code */
        for (int j118 = 0; j118 < 4; j118 = j118 + 1) {
            fRec34_tmp[j118] = fRec34_perm[j118];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec34[i] =
                fSlow44 * fRec34[i - 1] +
                fSlow45 * std::fabs(fConst100 * (fConst104 * fRec35[i] + fConst105 * fRec35[i - 1] +
                                                 fConst104 * fRec35[i - 2]));
        }
        /* Post code */
        for (int j119 = 0; j119 < 4; j119 = j119 + 1) {
            fRec34_perm[j119] = fRec34_tmp[vsize + j119];
        }
        /* Recursive loop 168 */
        /* Pre code */
        for (int j132 = 0; j132 < 4; j132 = j132 + 1) {
            fRec41_tmp[j132] = fRec41_perm[j132];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec41[i] =
                fSlow44 * fRec41[i - 1] +
                fSlow45 * std::fabs(fConst138 * (fConst142 * fRec42[i] + fConst143 * fRec42[i - 1] +
                                                 fConst142 * fRec42[i - 2]));
        }
        /* Post code */
        for (int j133 = 0; j133 < 4; j133 = j133 + 1) {
            fRec41_perm[j133] = fRec41_tmp[vsize + j133];
        }
        /* Recursive loop 169 */
        /* Pre code */
        for (int j146 = 0; j146 < 4; j146 = j146 + 1) {
            fRec48_tmp[j146] = fRec48_perm[j146];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec48[i] =
                fSlow44 * fRec48[i - 1] +
                fSlow45 * std::fabs(fConst176 * (fConst180 * fRec49[i] + fConst181 * fRec49[i - 1] +
                                                 fConst180 * fRec49[i - 2]));
        }
        /* Post code */
        for (int j147 = 0; j147 < 4; j147 = j147 + 1) {
            fRec48_perm[j147] = fRec48_tmp[vsize + j147];
        }
        /* Recursive loop 170 */
        /* Pre code */
        for (int j160 = 0; j160 < 4; j160 = j160 + 1) {
            fRec55_tmp[j160] = fRec55_perm[j160];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec55[i] =
                fSlow44 * fRec55[i - 1] +
                fSlow45 * std::fabs(fConst214 * (fConst218 * fRec56[i] + fConst219 * fRec56[i - 1] +
                                                 fConst218 * fRec56[i - 2]));
        }
        /* Post code */
        for (int j161 = 0; j161 < 4; j161 = j161 + 1) {
            fRec55_perm[j161] = fRec55_tmp[vsize + j161];
        }
        /* Recursive loop 171 */
        /* Pre code */
        for (int j174 = 0; j174 < 4; j174 = j174 + 1) {
            fRec62_tmp[j174] = fRec62_perm[j174];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec62[i] =
                fSlow44 * fRec62[i - 1] +
                fSlow45 * std::fabs(fConst252 * (fConst256 * fRec63[i] + fConst257 * fRec63[i - 1] +
                                                 fConst256 * fRec63[i - 2]));
        }
        /* Post code */
        for (int j175 = 0; j175 < 4; j175 = j175 + 1) {
            fRec62_perm[j175] = fRec62_tmp[vsize + j175];
        }
        /* Recursive loop 172 */
        /* Pre code */
        for (int j188 = 0; j188 < 4; j188 = j188 + 1) {
            fRec69_tmp[j188] = fRec69_perm[j188];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec69[i] =
                fSlow44 * fRec69[i - 1] +
                fSlow45 * std::fabs(fConst290 * (fConst294 * fRec70[i] + fConst295 * fRec70[i - 1] +
                                                 fConst294 * fRec70[i - 2]));
        }
        /* Post code */
        for (int j189 = 0; j189 < 4; j189 = j189 + 1) {
            fRec69_perm[j189] = fRec69_tmp[vsize + j189];
        }
        /* Recursive loop 173 */
        /* Pre code */
        for (int j202 = 0; j202 < 4; j202 = j202 + 1) {
            fRec76_tmp[j202] = fRec76_perm[j202];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec76[i] =
                fSlow44 * fRec76[i - 1] +
                fSlow45 * std::fabs(fConst328 * (fConst332 * fRec77[i] + fConst333 * fRec77[i - 1] +
                                                 fConst332 * fRec77[i - 2]));
        }
        /* Post code */
        for (int j203 = 0; j203 < 4; j203 = j203 + 1) {
            fRec76_perm[j203] = fRec76_tmp[vsize + j203];
        }
        /* Recursive loop 174 */
        /* Pre code */
        for (int j216 = 0; j216 < 4; j216 = j216 + 1) {
            fRec83_tmp[j216] = fRec83_perm[j216];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec83[i] =
                fSlow44 * fRec83[i - 1] +
                fSlow45 * std::fabs(fConst366 * (fConst370 * fRec84[i] + fConst371 * fRec84[i - 1] +
                                                 fConst370 * fRec84[i - 2]));
        }
        /* Post code */
        for (int j217 = 0; j217 < 4; j217 = j217 + 1) {
            fRec83_perm[j217] = fRec83_tmp[vsize + j217];
        }
        /* Recursive loop 175 */
        /* Pre code */
        for (int j230 = 0; j230 < 4; j230 = j230 + 1) {
            fRec90_tmp[j230] = fRec90_perm[j230];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec90[i] =
                fSlow44 * fRec90[i - 1] +
                fSlow45 * std::fabs(fConst404 * (fConst408 * fRec91[i] + fConst409 * fRec91[i - 1] +
                                                 fConst408 * fRec91[i - 2]));
        }
        /* Post code */
        for (int j231 = 0; j231 < 4; j231 = j231 + 1) {
            fRec90_perm[j231] = fRec90_tmp[vsize + j231];
        }
        /* Recursive loop 176 */
        /* Pre code */
        for (int j244 = 0; j244 < 4; j244 = j244 + 1) {
            fRec97_tmp[j244] = fRec97_perm[j244];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec97[i] =
                fSlow44 * fRec97[i - 1] +
                fSlow45 * std::fabs(fConst442 * (fConst446 * fRec98[i] + fConst447 * fRec98[i - 1] +
                                                 fConst446 * fRec98[i - 2]));
        }
        /* Post code */
        for (int j245 = 0; j245 < 4; j245 = j245 + 1) {
            fRec97_perm[j245] = fRec97_tmp[vsize + j245];
        }
        /* Recursive loop 177 */
        /* Pre code */
        for (int j258 = 0; j258 < 4; j258 = j258 + 1) {
            fRec104_tmp[j258] = fRec104_perm[j258];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec104[i] = fSlow44 * fRec104[i - 1] +
                         fSlow45 * std::fabs(fConst480 *
                                             (fConst484 * fRec105[i] + fConst485 * fRec105[i - 1] +
                                              fConst484 * fRec105[i - 2]));
        }
        /* Post code */
        for (int j259 = 0; j259 < 4; j259 = j259 + 1) {
            fRec104_perm[j259] = fRec104_tmp[vsize + j259];
        }
        /* Recursive loop 178 */
        /* Pre code */
        for (int j272 = 0; j272 < 4; j272 = j272 + 1) {
            fRec111_tmp[j272] = fRec111_perm[j272];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec111[i] = fSlow44 * fRec111[i - 1] +
                         fSlow45 * std::fabs(fConst518 *
                                             (fConst522 * fRec112[i] + fConst523 * fRec112[i - 1] +
                                              fConst522 * fRec112[i - 2]));
        }
        /* Post code */
        for (int j273 = 0; j273 < 4; j273 = j273 + 1) {
            fRec111_perm[j273] = fRec111_tmp[vsize + j273];
        }
        /* Recursive loop 179 */
        /* Pre code */
        for (int j280 = 0; j280 < 4; j280 = j280 + 1) {
            fRec118_tmp[j280] = fRec118_perm[j280];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec118[i] = fSlow44 * fRec118[i - 1] +
                         fSlow45 * std::fabs(fConst535 *
                                             (fConst538 * fRec119[i] + fConst539 * fRec119[i - 1] +
                                              fConst538 * fRec119[i - 2]));
        }
        /* Post code */
        for (int j281 = 0; j281 < 4; j281 = j281 + 1) {
            fRec118_perm[j281] = fRec118_tmp[vsize + j281];
        }
        /* Vectorizable loop 180 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fVbargraph0  = static_cast<FAUSTFLOAT>(fSlow46 + 2e+01 * std::log10(fRec23[i]));
            fVbargraph1  = static_cast<FAUSTFLOAT>(fSlow46 + 2e+01 * std::log10(fRec27[i]));
            fVbargraph2  = static_cast<FAUSTFLOAT>(fSlow46 + 2e+01 * std::log10(fRec34[i]));
            fVbargraph3  = static_cast<FAUSTFLOAT>(fSlow46 + 2e+01 * std::log10(fRec41[i]));
            fVbargraph4  = static_cast<FAUSTFLOAT>(fSlow46 + 2e+01 * std::log10(fRec48[i]));
            fVbargraph5  = static_cast<FAUSTFLOAT>(fSlow46 + 2e+01 * std::log10(fRec55[i]));
            fVbargraph6  = static_cast<FAUSTFLOAT>(fSlow46 + 2e+01 * std::log10(fRec62[i]));
            fVbargraph7  = static_cast<FAUSTFLOAT>(fSlow46 + 2e+01 * std::log10(fRec69[i]));
            fVbargraph8  = static_cast<FAUSTFLOAT>(fSlow46 + 2e+01 * std::log10(fRec76[i]));
            fVbargraph9  = static_cast<FAUSTFLOAT>(fSlow46 + 2e+01 * std::log10(fRec83[i]));
            fVbargraph10 = static_cast<FAUSTFLOAT>(fSlow46 + 2e+01 * std::log10(fRec90[i]));
            fVbargraph11 = static_cast<FAUSTFLOAT>(fSlow46 + 2e+01 * std::log10(fRec97[i]));
            fVbargraph12 = static_cast<FAUSTFLOAT>(fSlow46 + 2e+01 * std::log10(fRec104[i]));
            fVbargraph13 = static_cast<FAUSTFLOAT>(fSlow46 + 2e+01 * std::log10(fRec111[i]));
            fVbargraph14 = static_cast<FAUSTFLOAT>(fSlow46 + 2e+01 * std::log10(fRec118[i]));
            output0[i]   = static_cast<FAUSTFLOAT>(fZec44[i]);
        }
        /* Vectorizable loop 181 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            output1[i] = static_cast<FAUSTFLOAT>(fZec45[i]);
        }
    }
    /* Remaining frames */
    if (vindex < count) {
        FAUSTFLOAT* input0  = &input0_ptr[vindex];
        FAUSTFLOAT* output0 = &output0_ptr[vindex];
        FAUSTFLOAT* output1 = &output1_ptr[vindex];
        int         vsize   = count - vindex;
        /* Recursive loop 0 */
        /* Pre code */
        for (int j2 = 0; j2 < 4; j2 = j2 + 1) {
            fRec2_tmp[j2] = fRec2_perm[j2];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec2[i] = fRec2[i - 1] * fSlow2 + fSlow3;
        }
        /* Post code */
        for (int j3 = 0; j3 < 4; j3 = j3 + 1) {
            fRec2_perm[j3] = fRec2_tmp[vsize + j3];
        }
        /* Vectorizable loop 1 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec0[i] = std::max<double>(2e+01, std::fabs(fRec2[i]));
        }
        /* Vectorizable loop 2 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec2[i] = std::max<double>(2e+01, std::fabs(fSlow4 * fRec2[i]));
        }
        /* Vectorizable loop 3 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec4[i] = std::max<double>(2e+01, std::fabs(fSlow5 * fRec2[i]));
        }
        /* Recursive loop 4 */
        /* Pre code */
        for (int j4 = 0; j4 < 4; j4 = j4 + 1) {
            fRec1_tmp[j4] = fRec1_perm[j4];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec1[i] = fRec1[i - 1] + fConst1 * fZec0[i];
            fRec1[i] = fZec1[i] - std::floor(fZec1[i]);
        }
        /* Post code */
        for (int j5 = 0; j5 < 4; j5 = j5 + 1) {
            fRec1_perm[j5] = fRec1_tmp[vsize + j5];
        }
        /* Recursive loop 5 */
        /* Pre code */
        for (int j6 = 0; j6 < 4; j6 = j6 + 1) {
            fRec3_tmp[j6] = fRec3_perm[j6];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec3[i] = fRec3[i - 1] + fConst1 * fZec2[i];
            fRec3[i] = fZec3[i] - std::floor(fZec3[i]);
        }
        /* Post code */
        for (int j7 = 0; j7 < 4; j7 = j7 + 1) {
            fRec3_perm[j7] = fRec3_tmp[vsize + j7];
        }
        /* Recursive loop 6 */
        /* Pre code */
        for (int j8 = 0; j8 < 4; j8 = j8 + 1) {
            fRec4_tmp[j8] = fRec4_perm[j8];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec5[i] = fRec4[i - 1] + fConst1 * fZec4[i];
            fRec4[i] = fZec5[i] - std::floor(fZec5[i]);
        }
        /* Post code */
        for (int j9 = 0; j9 < 4; j9 = j9 + 1) {
            fRec4_perm[j9] = fRec4_tmp[vsize + j9];
        }
        /* Vectorizable loop 7 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec8[i] = 2.0 * fRec1[i];
        }
        /* Vectorizable loop 8 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec14[i] = 2.0 * fRec3[i];
        }
        /* Vectorizable loop 9 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec17[i] = 2.0 * fRec4[i];
        }
        /* Vectorizable loop 10 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec9[i] = fZec8[i] + -1.0;
        }
        /* Vectorizable loop 11 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec15[i] = fZec14[i] + -1.0;
        }
        /* Vectorizable loop 12 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec18[i] = fZec17[i] + -1.0;
        }
        /* Vectorizable loop 13 */
        /* Pre code */
        for (int j20 = 0; j20 < 4; j20 = j20 + 1) {
            fYec0_tmp[j20] = fYec0_perm[j20];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec0[i] = mydsp_faustpower2_f(fZec9[i]);
        }
        /* Post code */
        for (int j21 = 0; j21 < 4; j21 = j21 + 1) {
            fYec0_perm[j21] = fYec0_tmp[vsize + j21];
        }
        /* Vectorizable loop 14 */
        /* Pre code */
        for (int j32 = 0; j32 < 4; j32 = j32 + 1) {
            fYec6_tmp[j32] = fYec6_perm[j32];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec6[i] = mydsp_faustpower2_f(fZec15[i]);
        }
        /* Post code */
        for (int j33 = 0; j33 < 4; j33 = j33 + 1) {
            fYec6_perm[j33] = fYec6_tmp[vsize + j33];
        }
        /* Vectorizable loop 15 */
        /* Pre code */
        for (int j44 = 0; j44 < 4; j44 = j44 + 1) {
            fYec12_tmp[j44] = fYec12_perm[j44];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec12[i] = mydsp_faustpower2_f(fZec18[i]);
        }
        /* Post code */
        for (int j45 = 0; j45 < 4; j45 = j45 + 1) {
            fYec12_perm[j45] = fYec12_tmp[vsize + j45];
        }
        /* Recursive loop 16 */
        /* Pre code */
        for (int j10 = 0; j10 < 4; j10 = j10 + 1) {
            iRec5_tmp[j10] = iRec5_perm[j10];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iRec5[i] = 1103515245 * iRec5[i - 1] + 12345;
        }
        /* Post code */
        for (int j11 = 0; j11 < 4; j11 = j11 + 1) {
            iRec5_perm[j11] = iRec5_tmp[vsize + j11];
        }
        /* Vectorizable loop 17 */
        /* Pre code */
        for (int j16 = 0; j16 < 4; j16 = j16 + 1) {
            iVec0_tmp[j16] = iVec0_perm[j16];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iVec0[i] = 1;
        }
        /* Post code */
        for (int j17 = 0; j17 < 4; j17 = j17 + 1) {
            iVec0_perm[j17] = iVec0_tmp[vsize + j17];
        }
        /* Vectorizable loop 18 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec12[i] = mydsp_faustpower3_f(fZec9[i]);
        }
        /* Vectorizable loop 19 */
        /* Pre code */
        for (int j26 = 0; j26 < 4; j26 = j26 + 1) {
            fYec3_tmp[j26] = fYec3_perm[j26];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec3[i] = fYec0[i] * (fYec0[i] + -2.0);
        }
        /* Post code */
        for (int j27 = 0; j27 < 4; j27 = j27 + 1) {
            fYec3_perm[j27] = fYec3_tmp[vsize + j27];
        }
        /* Vectorizable loop 20 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec16[i] = mydsp_faustpower3_f(fZec15[i]);
        }
        /* Vectorizable loop 21 */
        /* Pre code */
        for (int j38 = 0; j38 < 4; j38 = j38 + 1) {
            fYec9_tmp[j38] = fYec9_perm[j38];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec9[i] = fYec6[i] * (fYec6[i] + -2.0);
        }
        /* Post code */
        for (int j39 = 0; j39 < 4; j39 = j39 + 1) {
            fYec9_perm[j39] = fYec9_tmp[vsize + j39];
        }
        /* Vectorizable loop 22 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec19[i] = mydsp_faustpower3_f(fZec18[i]);
        }
        /* Vectorizable loop 23 */
        /* Pre code */
        for (int j50 = 0; j50 < 4; j50 = j50 + 1) {
            fYec15_tmp[j50] = fYec15_perm[j50];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec15[i] = fYec12[i] * (fYec12[i] + -2.0);
        }
        /* Post code */
        for (int j51 = 0; j51 < 4; j51 = j51 + 1) {
            fYec15_perm[j51] = fYec15_tmp[vsize + j51];
        }
        /* Vectorizable loop 24 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec6[i] = 4.656612875245797e-10 * static_cast<double>(iRec5[i]);
        }
        /* Vectorizable loop 25 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec7[i] = static_cast<double>(1 - iVec0[i - 1]);
        }
        /* Vectorizable loop 26 */
        /* Pre code */
        for (int j22 = 0; j22 < 4; j22 = j22 + 1) {
            fYec1_tmp[j22] = fYec1_perm[j22];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec1[i] = fZec12[i] + (1.0 - fZec8[i]);
        }
        /* Post code */
        for (int j23 = 0; j23 < 4; j23 = j23 + 1) {
            fYec1_perm[j23] = fYec1_tmp[vsize + j23];
        }
        /* Vectorizable loop 27 */
        /* Pre code */
        for (int j28 = 0; j28 < 4; j28 = j28 + 1) {
            fYec4_tmp[j28] = fYec4_perm[j28];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec4[i] = (fYec3[i] - fYec3[i - 1]) / fZec0[i];
        }
        /* Post code */
        for (int j29 = 0; j29 < 4; j29 = j29 + 1) {
            fYec4_perm[j29] = fYec4_tmp[vsize + j29];
        }
        /* Vectorizable loop 28 */
        /* Pre code */
        for (int j34 = 0; j34 < 4; j34 = j34 + 1) {
            fYec7_tmp[j34] = fYec7_perm[j34];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec7[i] = fZec16[i] + (1.0 - fZec14[i]);
        }
        /* Post code */
        for (int j35 = 0; j35 < 4; j35 = j35 + 1) {
            fYec7_perm[j35] = fYec7_tmp[vsize + j35];
        }
        /* Vectorizable loop 29 */
        /* Pre code */
        for (int j40 = 0; j40 < 4; j40 = j40 + 1) {
            fYec10_tmp[j40] = fYec10_perm[j40];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec10[i] = (fYec9[i] - fYec9[i - 1]) / fZec2[i];
        }
        /* Post code */
        for (int j41 = 0; j41 < 4; j41 = j41 + 1) {
            fYec10_perm[j41] = fYec10_tmp[vsize + j41];
        }
        /* Vectorizable loop 30 */
        /* Pre code */
        for (int j46 = 0; j46 < 4; j46 = j46 + 1) {
            fYec13_tmp[j46] = fYec13_perm[j46];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec13[i] = fZec19[i] + (1.0 - fZec17[i]);
        }
        /* Post code */
        for (int j47 = 0; j47 < 4; j47 = j47 + 1) {
            fYec13_perm[j47] = fYec13_tmp[vsize + j47];
        }
        /* Vectorizable loop 31 */
        /* Pre code */
        for (int j52 = 0; j52 < 4; j52 = j52 + 1) {
            fYec16_tmp[j52] = fYec16_perm[j52];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec16[i] = (fYec15[i] - fYec15[i - 1]) / fZec4[i];
        }
        /* Post code */
        for (int j53 = 0; j53 < 4; j53 = j53 + 1) {
            fYec16_perm[j53] = fYec16_tmp[vsize + j53];
        }
        /* Recursive loop 32 */
        /* Pre code */
        for (int j0 = 0; j0 < 4; j0 = j0 + 1) {
            fRec0_tmp[j0] = fRec0_perm[j0];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec0[i] = fSlow0 + 0.999 * fRec0[i - 1];
        }
        /* Post code */
        for (int j1 = 0; j1 < 4; j1 = j1 + 1) {
            fRec0_perm[j1] = fRec0_tmp[vsize + j1];
        }
        /* Recursive loop 33 */
        /* Pre code */
        for (int j12 = 0; j12 < 4; j12 = j12 + 1) {
            fRec6_tmp[j12] = fRec6_perm[j12];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec6[i] = 0.5221894 * fRec6[i - 3] + fZec6[i] + 2.494956002 * fRec6[i - 1] -
                       2.017265875 * fRec6[i - 2];
        }
        /* Post code */
        for (int j13 = 0; j13 < 4; j13 = j13 + 1) {
            fRec6_perm[j13] = fRec6_tmp[vsize + j13];
        }
        /* Recursive loop 34 */
        /* Pre code */
        for (int j14 = 0; j14 < 4; j14 = j14 + 1) {
            fRec7_tmp[j14] = fRec7_perm[j14];
        }
        for (int j18 = 0; j18 < 4; j18 = j18 + 1) {
            fRec8_tmp[j18] = fRec8_perm[j18];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec7[i] = fSlow7 * fRec8[i - 1] + fSlow8 * fRec7[i - 1];
            fRec8[i] = fZec7[i] + fSlow8 * fRec8[i - 1] - fSlow7 * fRec7[i - 1];
        }
        /* Post code */
        for (int j15 = 0; j15 < 4; j15 = j15 + 1) {
            fRec7_perm[j15] = fRec7_tmp[vsize + j15];
        }
        for (int j19 = 0; j19 < 4; j19 = j19 + 1) {
            fRec8_perm[j19] = fRec8_tmp[vsize + j19];
        }
        /* Vectorizable loop 35 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec10[i] = static_cast<double>(iVec0[i - 1]);
        }
        /* Vectorizable loop 36 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec11[i] = static_cast<double>(iVec0[i - 2]);
        }
        /* Vectorizable loop 37 */
        /* Pre code */
        for (int j24 = 0; j24 < 4; j24 = j24 + 1) {
            fYec2_tmp[j24] = fYec2_perm[j24];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec2[i] = (fZec12[i] + (1.0 - (fZec8[i] + fYec1[i - 1]))) / fZec0[i];
        }
        /* Post code */
        for (int j25 = 0; j25 < 4; j25 = j25 + 1) {
            fYec2_perm[j25] = fYec2_tmp[vsize + j25];
        }
        /* Vectorizable loop 38 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec13[i] = static_cast<double>(iVec0[i - 3]);
        }
        /* Vectorizable loop 39 */
        /* Pre code */
        for (int j30 = 0; j30 < 4; j30 = j30 + 1) {
            fYec5_tmp[j30] = fYec5_perm[j30];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec5[i] = (fYec4[i] - fYec4[i - 1]) / fZec0[i];
        }
        /* Post code */
        for (int j31 = 0; j31 < 4; j31 = j31 + 1) {
            fYec5_perm[j31] = fYec5_tmp[vsize + j31];
        }
        /* Vectorizable loop 40 */
        /* Pre code */
        for (int j36 = 0; j36 < 4; j36 = j36 + 1) {
            fYec8_tmp[j36] = fYec8_perm[j36];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec8[i] = (fZec16[i] + (1.0 - (fZec14[i] + fYec7[i - 1]))) / fZec2[i];
        }
        /* Post code */
        for (int j37 = 0; j37 < 4; j37 = j37 + 1) {
            fYec8_perm[j37] = fYec8_tmp[vsize + j37];
        }
        /* Vectorizable loop 41 */
        /* Pre code */
        for (int j42 = 0; j42 < 4; j42 = j42 + 1) {
            fYec11_tmp[j42] = fYec11_perm[j42];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec11[i] = (fYec10[i] - fYec10[i - 1]) / fZec2[i];
        }
        /* Post code */
        for (int j43 = 0; j43 < 4; j43 = j43 + 1) {
            fYec11_perm[j43] = fYec11_tmp[vsize + j43];
        }
        /* Vectorizable loop 42 */
        /* Pre code */
        for (int j48 = 0; j48 < 4; j48 = j48 + 1) {
            fYec14_tmp[j48] = fYec14_perm[j48];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec14[i] = (fZec19[i] + (1.0 - (fZec17[i] + fYec13[i - 1]))) / fZec4[i];
        }
        /* Post code */
        for (int j49 = 0; j49 < 4; j49 = j49 + 1) {
            fYec14_perm[j49] = fYec14_tmp[vsize + j49];
        }
        /* Vectorizable loop 43 */
        /* Pre code */
        for (int j54 = 0; j54 < 4; j54 = j54 + 1) {
            fYec17_tmp[j54] = fYec17_perm[j54];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec17[i] = (fYec16[i] - fYec16[i - 1]) / fZec4[i];
        }
        /* Post code */
        for (int j55 = 0; j55 < 4; j55 = j55 + 1) {
            fYec17_perm[j55] = fYec17_tmp[vsize + j55];
        }
        /* Vectorizable loop 44 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec20[i] =
                fRec0[i] *
                ((iSlow12)
                     ? static_cast<double>(input0[i])
                     : ((iSlow13)
                            ? ((iSlow18)
                                   ? 0.049922035 * fRec6[i] + 0.050612699 * fRec6[i - 2] -
                                         (0.095993537 * fRec6[i - 1] + 0.004408786 * fRec6[i - 3])
                                   : fZec6[i])
                            : 0.3333333333333333 * fRec0[i] *
                                  (((iSlow15)
                                        ? ((iSlow17)
                                               ? fConst5 * (fZec13[i] * (fYec5[i] - fYec5[i - 1]) /
                                                            fZec0[i])
                                               : fConst4 * (fZec11[i] * (fYec2[i] - fYec2[i - 1]) /
                                                            fZec0[i]))
                                        : ((iSlow16)
                                               ? fConst3 * (fZec10[i] * (fYec0[i] - fYec0[i - 1]) /
                                                            fZec0[i])
                                               : fZec9[i])) +
                                   ((iSlow15)
                                        ? ((iSlow17)
                                               ? fConst5 * (fZec13[i] *
                                                            (fYec11[i] - fYec11[i - 1]) / fZec2[i])
                                               : fConst4 * (fZec11[i] * (fYec8[i] - fYec8[i - 1]) /
                                                            fZec2[i]))
                                        : ((iSlow16)
                                               ? fConst3 * (fZec10[i] * (fYec6[i] - fYec6[i - 1]) /
                                                            fZec2[i])
                                               : fZec15[i])) +
                                   ((iSlow15)
                                        ? ((iSlow17)
                                               ? fConst5 * (fZec13[i] *
                                                            (fYec17[i] - fYec17[i - 1]) / fZec4[i])
                                               : fConst4 * (fZec11[i] *
                                                            (fYec14[i] - fYec14[i - 1]) / fZec4[i]))
                                        : ((iSlow16)
                                               ? fConst3 * (fZec10[i] *
                                                            (fYec12[i] - fYec12[i - 1]) / fZec4[i])
                                               : fZec18[i])))));
        }
        /* Vectorizable loop 45 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec23[i] = fConst0 * (fSlow19 + fSlow20 * (fRec7[i] + 1.0));
        }
        /* Vectorizable loop 46 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec34[i] = fConst0 * (fSlow19 + fSlow20 * (fRec8[i] + 1.0));
        }
        /* Vectorizable loop 47 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec21[i] = ((iSlow11) ? 0.0 : fZec20[i]);
        }
        /* Vectorizable loop 48 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iZec24[i] = static_cast<int>(fZec23[i]);
        }
        /* Vectorizable loop 49 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            iZec35[i] = static_cast<int>(fZec34[i]);
        }
        /* Vectorizable loop 50 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fHbargraph0 = static_cast<FAUSTFLOAT>(fRec8[i] + fRec7[i]);
            fZec22[i]   = fSlow10 * fZec21[i];
        }
        /* Vectorizable loop 51 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec25[i] = static_cast<double>(iZec24[i]);
        }
        /* Vectorizable loop 52 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec33[i] = fSlow10 * fZec21[i];
        }
        /* Vectorizable loop 53 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec36[i] = static_cast<double>(iZec35[i]);
        }
        /* Recursive loop 54 */
        /* Pre code */
        fYec18_idx = (fYec18_idx + fYec18_idx_save) & 4095;
        for (int j56 = 0; j56 < 4; j56 = j56 + 1) {
            fRec9_tmp[j56] = fRec9_perm[j56];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec18[(i + fYec18_idx) & 4095] = fSlow9 * fRec9[i - 1] - fZec22[i];
            fRec9[i] = fYec18[(i + fYec18_idx - (iZec24[i] & 2047)) & 4095] *
                           (fZec25[i] + (1.0 - fZec23[i])) +
                       (fZec23[i] - fZec25[i]) *
                           fYec18[(i + fYec18_idx - ((iZec24[i] + 1) & 2047)) & 4095];
        }
        /* Post code */
        fYec18_idx_save = vsize;
        for (int j57 = 0; j57 < 4; j57 = j57 + 1) {
            fRec9_perm[j57] = fRec9_tmp[vsize + j57];
        }
        /* Recursive loop 55 */
        /* Pre code */
        fYec19_idx = (fYec19_idx + fYec19_idx_save) & 4095;
        for (int j72 = 0; j72 < 4; j72 = j72 + 1) {
            fRec17_tmp[j72] = fRec17_perm[j72];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fYec19[(i + fYec19_idx) & 4095] = fSlow9 * fRec17[i - 1] - fZec33[i];
            fRec17[i] = fYec19[(i + fYec19_idx - (iZec35[i] & 2047)) & 4095] *
                            (fZec36[i] + (1.0 - fZec34[i])) +
                        (fZec34[i] - fZec36[i]) *
                            fYec19[(i + fYec19_idx - ((iZec35[i] + 1) & 2047)) & 4095];
        }
        /* Post code */
        fYec19_idx_save = vsize;
        for (int j73 = 0; j73 < 4; j73 = j73 + 1) {
            fRec17_perm[j73] = fRec17_tmp[vsize + j73];
        }
        /* Recursive loop 56 */
        /* Pre code */
        for (int j58 = 0; j58 < 4; j58 = j58 + 1) {
            fRec15_tmp[j58] = fRec15_perm[j58];
        }
        for (int j60 = 0; j60 < 4; j60 = j60 + 1) {
            fRec16_tmp[j60] = fRec16_perm[j60];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec15[i] = fSlow22 * fRec16[i - 1] + fSlow23 * fRec15[i - 1];
            fRec16[i] = fZec7[i] + fSlow23 * fRec16[i - 1] - fSlow22 * fRec15[i - 1];
        }
        /* Post code */
        for (int j59 = 0; j59 < 4; j59 = j59 + 1) {
            fRec15_perm[j59] = fRec15_tmp[vsize + j59];
        }
        for (int j61 = 0; j61 < 4; j61 = j61 + 1) {
            fRec16_perm[j61] = fRec16_tmp[vsize + j61];
        }
        /* Vectorizable loop 57 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec26[i] = ((iSlow11) ? fZec20[i] : 0.5 * (fZec22[i] + fRec9[i] * fSlow27));
        }
        /* Vectorizable loop 58 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec37[i] = ((iSlow11) ? fZec20[i] : 0.5 * (fZec33[i] + fRec17[i] * fSlow27));
        }
        /* Vectorizable loop 59 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec27[i] = ((iSlow25) ? 0.0 : fZec26[i]);
        }
        /* Vectorizable loop 60 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec28[i] = fSlow34 - fSlow35 * (1.0 - fRec15[i]);
        }
        /* Vectorizable loop 61 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec38[i] = ((iSlow25) ? 0.0 : fZec37[i]);
        }
        /* Vectorizable loop 62 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec39[i] = fSlow34 - fSlow35 * (1.0 - fRec16[i]);
        }
        /* Recursive loop 63 */
        /* Pre code */
        for (int j62 = 0; j62 < 4; j62 = j62 + 1) {
            fRec14_tmp[j62] = fRec14_perm[j62];
        }
        for (int j64 = 0; j64 < 4; j64 = j64 + 1) {
            fRec13_tmp[j64] = fRec13_perm[j64];
        }
        for (int j66 = 0; j66 < 4; j66 = j66 + 1) {
            fRec12_tmp[j66] = fRec12_perm[j66];
        }
        for (int j68 = 0; j68 < 4; j68 = j68 + 1) {
            fRec11_tmp[j68] = fRec11_perm[j68];
        }
        for (int j70 = 0; j70 < 4; j70 = j70 + 1) {
            fRec10_tmp[j70] = fRec10_perm[j70];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec29[i] = fRec14[i - 1] * std::cos(fSlow32 * fZec28[i]);
            fRec14[i] = fSlow24 * fZec27[i] + fSlow28 * fRec10[i - 1] + fSlow30 * fZec29[i] -
                        fSlow36 * fRec14[i - 2];
            fZec30[i] = fRec13[i - 1] * std::cos(fSlow37 * fZec28[i]);
            fRec13[i] = fRec14[i - 2] + fSlow36 * (fRec14[i] - fRec13[i - 2]) -
                        fSlow30 * (fZec29[i] - fZec30[i]);
            fZec31[i] = fRec12[i - 1] * std::cos(fSlow38 * fZec28[i]);
            fRec12[i] = fRec13[i - 2] + fSlow36 * (fRec13[i] - fRec12[i - 2]) -
                        fSlow30 * (fZec30[i] - fZec31[i]);
            fZec32[i] = fRec11[i - 1] * std::cos(fSlow39 * fZec28[i]);
            fRec11[i] = fRec12[i - 2] + fSlow36 * (fRec12[i] - fRec11[i - 2]) -
                        fSlow30 * (fZec31[i] - fZec32[i]);
            fRec10[i] = fRec11[i - 2] + fSlow36 * fRec11[i] - fSlow30 * fZec32[i];
        }
        /* Post code */
        for (int j63 = 0; j63 < 4; j63 = j63 + 1) {
            fRec14_perm[j63] = fRec14_tmp[vsize + j63];
        }
        for (int j65 = 0; j65 < 4; j65 = j65 + 1) {
            fRec13_perm[j65] = fRec13_tmp[vsize + j65];
        }
        for (int j67 = 0; j67 < 4; j67 = j67 + 1) {
            fRec12_perm[j67] = fRec12_tmp[vsize + j67];
        }
        for (int j69 = 0; j69 < 4; j69 = j69 + 1) {
            fRec11_perm[j69] = fRec11_tmp[vsize + j69];
        }
        for (int j71 = 0; j71 < 4; j71 = j71 + 1) {
            fRec10_perm[j71] = fRec10_tmp[vsize + j71];
        }
        /* Recursive loop 64 */
        /* Pre code */
        for (int j74 = 0; j74 < 4; j74 = j74 + 1) {
            fRec22_tmp[j74] = fRec22_perm[j74];
        }
        for (int j76 = 0; j76 < 4; j76 = j76 + 1) {
            fRec21_tmp[j76] = fRec21_perm[j76];
        }
        for (int j78 = 0; j78 < 4; j78 = j78 + 1) {
            fRec20_tmp[j78] = fRec20_perm[j78];
        }
        for (int j80 = 0; j80 < 4; j80 = j80 + 1) {
            fRec19_tmp[j80] = fRec19_perm[j80];
        }
        for (int j82 = 0; j82 < 4; j82 = j82 + 1) {
            fRec18_tmp[j82] = fRec18_perm[j82];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec40[i] = fRec22[i - 1] * std::cos(fSlow32 * fZec39[i]);
            fRec22[i] = fSlow24 * fZec38[i] + fSlow28 * fRec18[i - 1] + fSlow30 * fZec40[i] -
                        fSlow36 * fRec22[i - 2];
            fZec41[i] = fRec21[i - 1] * std::cos(fSlow37 * fZec39[i]);
            fRec21[i] = fRec22[i - 2] + fSlow36 * (fRec22[i] - fRec21[i - 2]) -
                        fSlow30 * (fZec40[i] - fZec41[i]);
            fZec42[i] = fRec20[i - 1] * std::cos(fSlow38 * fZec39[i]);
            fRec20[i] = fRec21[i - 2] + fSlow36 * (fRec21[i] - fRec20[i - 2]) -
                        fSlow30 * (fZec41[i] - fZec42[i]);
            fZec43[i] = fRec19[i - 1] * std::cos(fSlow39 * fZec39[i]);
            fRec19[i] = fRec20[i - 2] + fSlow36 * (fRec20[i] - fRec19[i - 2]) -
                        fSlow30 * (fZec42[i] - fZec43[i]);
            fRec18[i] = fRec19[i - 2] + fSlow36 * fRec19[i] - fSlow30 * fZec43[i];
        }
        /* Post code */
        for (int j75 = 0; j75 < 4; j75 = j75 + 1) {
            fRec22_perm[j75] = fRec22_tmp[vsize + j75];
        }
        for (int j77 = 0; j77 < 4; j77 = j77 + 1) {
            fRec21_perm[j77] = fRec21_tmp[vsize + j77];
        }
        for (int j79 = 0; j79 < 4; j79 = j79 + 1) {
            fRec20_perm[j79] = fRec20_tmp[vsize + j79];
        }
        for (int j81 = 0; j81 < 4; j81 = j81 + 1) {
            fRec19_perm[j81] = fRec19_tmp[vsize + j81];
        }
        for (int j83 = 0; j83 < 4; j83 = j83 + 1) {
            fRec18_perm[j83] = fRec18_tmp[vsize + j83];
        }
        /* Vectorizable loop 65 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec44[i] =
                ((iSlow25) ? fZec26[i] : fSlow24 * fZec27[i] * fSlow41 + fRec10[i] * fSlow42);
        }
        /* Vectorizable loop 66 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec45[i] =
                ((iSlow25) ? fZec37[i] : fSlow24 * fSlow41 * fZec38[i] + fRec18[i] * fSlow42);
        }
        /* Vectorizable loop 67 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec46[i] = fZec44[i] + fZec45[i];
        }
        /* Recursive loop 68 */
        /* Pre code */
        for (int j92 = 0; j92 < 4; j92 = j92 + 1) {
            fRec33_tmp[j92] = fRec33_perm[j92];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec33[i] =
                fZec46[i] - fConst30 * (fConst31 * fRec33[i - 2] + fConst32 * fRec33[i - 1]);
        }
        /* Post code */
        for (int j93 = 0; j93 < 4; j93 = j93 + 1) {
            fRec33_perm[j93] = fRec33_tmp[vsize + j93];
        }
        /* Recursive loop 69 */
        /* Pre code */
        for (int j94 = 0; j94 < 4; j94 = j94 + 1) {
            fRec32_tmp[j94] = fRec32_perm[j94];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec32[i] = fConst30 * (fConst34 * fRec33[i] + fConst35 * fRec33[i - 1] +
                                    fConst34 * fRec33[i - 2]) -
                        fConst36 * (fConst37 * fRec32[i - 2] + fConst38 * fRec32[i - 1]);
        }
        /* Post code */
        for (int j95 = 0; j95 < 4; j95 = j95 + 1) {
            fRec32_perm[j95] = fRec32_tmp[vsize + j95];
        }
        /* Recursive loop 70 */
        /* Pre code */
        for (int j96 = 0; j96 < 4; j96 = j96 + 1) {
            fRec31_tmp[j96] = fRec31_perm[j96];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec31[i] = fConst36 * (fConst39 * fRec32[i] + fConst40 * fRec32[i - 1] +
                                    fConst39 * fRec32[i - 2]) -
                        fConst41 * (fConst42 * fRec31[i - 2] + fConst43 * fRec31[i - 1]);
        }
        /* Post code */
        for (int j97 = 0; j97 < 4; j97 = j97 + 1) {
            fRec31_perm[j97] = fRec31_tmp[vsize + j97];
        }
        /* Vectorizable loop 71 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec47[i] = fConst41 * (fConst44 * fRec31[i] + fConst45 * fRec31[i - 1] +
                                    fConst44 * fRec31[i - 2]);
        }
        /* Recursive loop 72 */
        /* Pre code */
        for (int j106 = 0; j106 < 4; j106 = j106 + 1) {
            fRec40_tmp[j106] = fRec40_perm[j106];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec40[i] =
                fZec47[i] - fConst68 * (fConst69 * fRec40[i - 2] + fConst70 * fRec40[i - 1]);
        }
        /* Post code */
        for (int j107 = 0; j107 < 4; j107 = j107 + 1) {
            fRec40_perm[j107] = fRec40_tmp[vsize + j107];
        }
        /* Recursive loop 73 */
        /* Pre code */
        for (int j108 = 0; j108 < 4; j108 = j108 + 1) {
            fRec39_tmp[j108] = fRec39_perm[j108];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec39[i] = fConst68 * (fConst72 * fRec40[i] + fConst73 * fRec40[i - 1] +
                                    fConst72 * fRec40[i - 2]) -
                        fConst74 * (fConst75 * fRec39[i - 2] + fConst76 * fRec39[i - 1]);
        }
        /* Post code */
        for (int j109 = 0; j109 < 4; j109 = j109 + 1) {
            fRec39_perm[j109] = fRec39_tmp[vsize + j109];
        }
        /* Recursive loop 74 */
        /* Pre code */
        for (int j110 = 0; j110 < 4; j110 = j110 + 1) {
            fRec38_tmp[j110] = fRec38_perm[j110];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec38[i] = fConst74 * (fConst77 * fRec39[i] + fConst78 * fRec39[i - 1] +
                                    fConst77 * fRec39[i - 2]) -
                        fConst79 * (fConst80 * fRec38[i - 2] + fConst81 * fRec38[i - 1]);
        }
        /* Post code */
        for (int j111 = 0; j111 < 4; j111 = j111 + 1) {
            fRec38_perm[j111] = fRec38_tmp[vsize + j111];
        }
        /* Vectorizable loop 75 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec48[i] = fConst79 * (fConst82 * fRec38[i] + fConst83 * fRec38[i - 1] +
                                    fConst82 * fRec38[i - 2]);
        }
        /* Recursive loop 76 */
        /* Pre code */
        for (int j120 = 0; j120 < 4; j120 = j120 + 1) {
            fRec47_tmp[j120] = fRec47_perm[j120];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec47[i] =
                fZec48[i] - fConst106 * (fConst107 * fRec47[i - 2] + fConst108 * fRec47[i - 1]);
        }
        /* Post code */
        for (int j121 = 0; j121 < 4; j121 = j121 + 1) {
            fRec47_perm[j121] = fRec47_tmp[vsize + j121];
        }
        /* Recursive loop 77 */
        /* Pre code */
        for (int j122 = 0; j122 < 4; j122 = j122 + 1) {
            fRec46_tmp[j122] = fRec46_perm[j122];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec46[i] = fConst106 * (fConst110 * fRec47[i] + fConst111 * fRec47[i - 1] +
                                     fConst110 * fRec47[i - 2]) -
                        fConst112 * (fConst113 * fRec46[i - 2] + fConst114 * fRec46[i - 1]);
        }
        /* Post code */
        for (int j123 = 0; j123 < 4; j123 = j123 + 1) {
            fRec46_perm[j123] = fRec46_tmp[vsize + j123];
        }
        /* Recursive loop 78 */
        /* Pre code */
        for (int j124 = 0; j124 < 4; j124 = j124 + 1) {
            fRec45_tmp[j124] = fRec45_perm[j124];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec45[i] = fConst112 * (fConst115 * fRec46[i] + fConst116 * fRec46[i - 1] +
                                     fConst115 * fRec46[i - 2]) -
                        fConst117 * (fConst118 * fRec45[i - 2] + fConst119 * fRec45[i - 1]);
        }
        /* Post code */
        for (int j125 = 0; j125 < 4; j125 = j125 + 1) {
            fRec45_perm[j125] = fRec45_tmp[vsize + j125];
        }
        /* Vectorizable loop 79 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec49[i] = fConst117 * (fConst120 * fRec45[i] + fConst121 * fRec45[i - 1] +
                                     fConst120 * fRec45[i - 2]);
        }
        /* Recursive loop 80 */
        /* Pre code */
        for (int j134 = 0; j134 < 4; j134 = j134 + 1) {
            fRec54_tmp[j134] = fRec54_perm[j134];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec54[i] =
                fZec49[i] - fConst144 * (fConst145 * fRec54[i - 2] + fConst146 * fRec54[i - 1]);
        }
        /* Post code */
        for (int j135 = 0; j135 < 4; j135 = j135 + 1) {
            fRec54_perm[j135] = fRec54_tmp[vsize + j135];
        }
        /* Recursive loop 81 */
        /* Pre code */
        for (int j136 = 0; j136 < 4; j136 = j136 + 1) {
            fRec53_tmp[j136] = fRec53_perm[j136];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec53[i] = fConst144 * (fConst148 * fRec54[i] + fConst149 * fRec54[i - 1] +
                                     fConst148 * fRec54[i - 2]) -
                        fConst150 * (fConst151 * fRec53[i - 2] + fConst152 * fRec53[i - 1]);
        }
        /* Post code */
        for (int j137 = 0; j137 < 4; j137 = j137 + 1) {
            fRec53_perm[j137] = fRec53_tmp[vsize + j137];
        }
        /* Recursive loop 82 */
        /* Pre code */
        for (int j138 = 0; j138 < 4; j138 = j138 + 1) {
            fRec52_tmp[j138] = fRec52_perm[j138];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec52[i] = fConst150 * (fConst153 * fRec53[i] + fConst154 * fRec53[i - 1] +
                                     fConst153 * fRec53[i - 2]) -
                        fConst155 * (fConst156 * fRec52[i - 2] + fConst157 * fRec52[i - 1]);
        }
        /* Post code */
        for (int j139 = 0; j139 < 4; j139 = j139 + 1) {
            fRec52_perm[j139] = fRec52_tmp[vsize + j139];
        }
        /* Vectorizable loop 83 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec50[i] = fConst155 * (fConst158 * fRec52[i] + fConst159 * fRec52[i - 1] +
                                     fConst158 * fRec52[i - 2]);
        }
        /* Recursive loop 84 */
        /* Pre code */
        for (int j148 = 0; j148 < 4; j148 = j148 + 1) {
            fRec61_tmp[j148] = fRec61_perm[j148];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec61[i] =
                fZec50[i] - fConst182 * (fConst183 * fRec61[i - 2] + fConst184 * fRec61[i - 1]);
        }
        /* Post code */
        for (int j149 = 0; j149 < 4; j149 = j149 + 1) {
            fRec61_perm[j149] = fRec61_tmp[vsize + j149];
        }
        /* Recursive loop 85 */
        /* Pre code */
        for (int j150 = 0; j150 < 4; j150 = j150 + 1) {
            fRec60_tmp[j150] = fRec60_perm[j150];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec60[i] = fConst182 * (fConst186 * fRec61[i] + fConst187 * fRec61[i - 1] +
                                     fConst186 * fRec61[i - 2]) -
                        fConst188 * (fConst189 * fRec60[i - 2] + fConst190 * fRec60[i - 1]);
        }
        /* Post code */
        for (int j151 = 0; j151 < 4; j151 = j151 + 1) {
            fRec60_perm[j151] = fRec60_tmp[vsize + j151];
        }
        /* Recursive loop 86 */
        /* Pre code */
        for (int j152 = 0; j152 < 4; j152 = j152 + 1) {
            fRec59_tmp[j152] = fRec59_perm[j152];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec59[i] = fConst188 * (fConst191 * fRec60[i] + fConst192 * fRec60[i - 1] +
                                     fConst191 * fRec60[i - 2]) -
                        fConst193 * (fConst194 * fRec59[i - 2] + fConst195 * fRec59[i - 1]);
        }
        /* Post code */
        for (int j153 = 0; j153 < 4; j153 = j153 + 1) {
            fRec59_perm[j153] = fRec59_tmp[vsize + j153];
        }
        /* Vectorizable loop 87 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec51[i] = fConst193 * (fConst196 * fRec59[i] + fConst197 * fRec59[i - 1] +
                                     fConst196 * fRec59[i - 2]);
        }
        /* Recursive loop 88 */
        /* Pre code */
        for (int j162 = 0; j162 < 4; j162 = j162 + 1) {
            fRec68_tmp[j162] = fRec68_perm[j162];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec68[i] =
                fZec51[i] - fConst220 * (fConst221 * fRec68[i - 2] + fConst222 * fRec68[i - 1]);
        }
        /* Post code */
        for (int j163 = 0; j163 < 4; j163 = j163 + 1) {
            fRec68_perm[j163] = fRec68_tmp[vsize + j163];
        }
        /* Recursive loop 89 */
        /* Pre code */
        for (int j164 = 0; j164 < 4; j164 = j164 + 1) {
            fRec67_tmp[j164] = fRec67_perm[j164];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec67[i] = fConst220 * (fConst224 * fRec68[i] + fConst225 * fRec68[i - 1] +
                                     fConst224 * fRec68[i - 2]) -
                        fConst226 * (fConst227 * fRec67[i - 2] + fConst228 * fRec67[i - 1]);
        }
        /* Post code */
        for (int j165 = 0; j165 < 4; j165 = j165 + 1) {
            fRec67_perm[j165] = fRec67_tmp[vsize + j165];
        }
        /* Recursive loop 90 */
        /* Pre code */
        for (int j166 = 0; j166 < 4; j166 = j166 + 1) {
            fRec66_tmp[j166] = fRec66_perm[j166];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec66[i] = fConst226 * (fConst229 * fRec67[i] + fConst230 * fRec67[i - 1] +
                                     fConst229 * fRec67[i - 2]) -
                        fConst231 * (fConst232 * fRec66[i - 2] + fConst233 * fRec66[i - 1]);
        }
        /* Post code */
        for (int j167 = 0; j167 < 4; j167 = j167 + 1) {
            fRec66_perm[j167] = fRec66_tmp[vsize + j167];
        }
        /* Vectorizable loop 91 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec52[i] = fConst231 * (fConst234 * fRec66[i] + fConst235 * fRec66[i - 1] +
                                     fConst234 * fRec66[i - 2]);
        }
        /* Recursive loop 92 */
        /* Pre code */
        for (int j176 = 0; j176 < 4; j176 = j176 + 1) {
            fRec75_tmp[j176] = fRec75_perm[j176];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec75[i] =
                fZec52[i] - fConst258 * (fConst259 * fRec75[i - 2] + fConst260 * fRec75[i - 1]);
        }
        /* Post code */
        for (int j177 = 0; j177 < 4; j177 = j177 + 1) {
            fRec75_perm[j177] = fRec75_tmp[vsize + j177];
        }
        /* Recursive loop 93 */
        /* Pre code */
        for (int j178 = 0; j178 < 4; j178 = j178 + 1) {
            fRec74_tmp[j178] = fRec74_perm[j178];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec74[i] = fConst258 * (fConst262 * fRec75[i] + fConst263 * fRec75[i - 1] +
                                     fConst262 * fRec75[i - 2]) -
                        fConst264 * (fConst265 * fRec74[i - 2] + fConst266 * fRec74[i - 1]);
        }
        /* Post code */
        for (int j179 = 0; j179 < 4; j179 = j179 + 1) {
            fRec74_perm[j179] = fRec74_tmp[vsize + j179];
        }
        /* Recursive loop 94 */
        /* Pre code */
        for (int j180 = 0; j180 < 4; j180 = j180 + 1) {
            fRec73_tmp[j180] = fRec73_perm[j180];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec73[i] = fConst264 * (fConst267 * fRec74[i] + fConst268 * fRec74[i - 1] +
                                     fConst267 * fRec74[i - 2]) -
                        fConst269 * (fConst270 * fRec73[i - 2] + fConst271 * fRec73[i - 1]);
        }
        /* Post code */
        for (int j181 = 0; j181 < 4; j181 = j181 + 1) {
            fRec73_perm[j181] = fRec73_tmp[vsize + j181];
        }
        /* Vectorizable loop 95 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec53[i] = fConst269 * (fConst272 * fRec73[i] + fConst273 * fRec73[i - 1] +
                                     fConst272 * fRec73[i - 2]);
        }
        /* Recursive loop 96 */
        /* Pre code */
        for (int j190 = 0; j190 < 4; j190 = j190 + 1) {
            fRec82_tmp[j190] = fRec82_perm[j190];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec82[i] =
                fZec53[i] - fConst296 * (fConst297 * fRec82[i - 2] + fConst298 * fRec82[i - 1]);
        }
        /* Post code */
        for (int j191 = 0; j191 < 4; j191 = j191 + 1) {
            fRec82_perm[j191] = fRec82_tmp[vsize + j191];
        }
        /* Recursive loop 97 */
        /* Pre code */
        for (int j192 = 0; j192 < 4; j192 = j192 + 1) {
            fRec81_tmp[j192] = fRec81_perm[j192];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec81[i] = fConst296 * (fConst300 * fRec82[i] + fConst301 * fRec82[i - 1] +
                                     fConst300 * fRec82[i - 2]) -
                        fConst302 * (fConst303 * fRec81[i - 2] + fConst304 * fRec81[i - 1]);
        }
        /* Post code */
        for (int j193 = 0; j193 < 4; j193 = j193 + 1) {
            fRec81_perm[j193] = fRec81_tmp[vsize + j193];
        }
        /* Recursive loop 98 */
        /* Pre code */
        for (int j194 = 0; j194 < 4; j194 = j194 + 1) {
            fRec80_tmp[j194] = fRec80_perm[j194];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec80[i] = fConst302 * (fConst305 * fRec81[i] + fConst306 * fRec81[i - 1] +
                                     fConst305 * fRec81[i - 2]) -
                        fConst307 * (fConst308 * fRec80[i - 2] + fConst309 * fRec80[i - 1]);
        }
        /* Post code */
        for (int j195 = 0; j195 < 4; j195 = j195 + 1) {
            fRec80_perm[j195] = fRec80_tmp[vsize + j195];
        }
        /* Vectorizable loop 99 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec54[i] = fConst307 * (fConst310 * fRec80[i] + fConst311 * fRec80[i - 1] +
                                     fConst310 * fRec80[i - 2]);
        }
        /* Recursive loop 100 */
        /* Pre code */
        for (int j204 = 0; j204 < 4; j204 = j204 + 1) {
            fRec89_tmp[j204] = fRec89_perm[j204];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec89[i] =
                fZec54[i] - fConst334 * (fConst335 * fRec89[i - 2] + fConst336 * fRec89[i - 1]);
        }
        /* Post code */
        for (int j205 = 0; j205 < 4; j205 = j205 + 1) {
            fRec89_perm[j205] = fRec89_tmp[vsize + j205];
        }
        /* Recursive loop 101 */
        /* Pre code */
        for (int j206 = 0; j206 < 4; j206 = j206 + 1) {
            fRec88_tmp[j206] = fRec88_perm[j206];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec88[i] = fConst334 * (fConst338 * fRec89[i] + fConst339 * fRec89[i - 1] +
                                     fConst338 * fRec89[i - 2]) -
                        fConst340 * (fConst341 * fRec88[i - 2] + fConst342 * fRec88[i - 1]);
        }
        /* Post code */
        for (int j207 = 0; j207 < 4; j207 = j207 + 1) {
            fRec88_perm[j207] = fRec88_tmp[vsize + j207];
        }
        /* Recursive loop 102 */
        /* Pre code */
        for (int j208 = 0; j208 < 4; j208 = j208 + 1) {
            fRec87_tmp[j208] = fRec87_perm[j208];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec87[i] = fConst340 * (fConst343 * fRec88[i] + fConst344 * fRec88[i - 1] +
                                     fConst343 * fRec88[i - 2]) -
                        fConst345 * (fConst346 * fRec87[i - 2] + fConst347 * fRec87[i - 1]);
        }
        /* Post code */
        for (int j209 = 0; j209 < 4; j209 = j209 + 1) {
            fRec87_perm[j209] = fRec87_tmp[vsize + j209];
        }
        /* Vectorizable loop 103 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec55[i] = fConst345 * (fConst348 * fRec87[i] + fConst349 * fRec87[i - 1] +
                                     fConst348 * fRec87[i - 2]);
        }
        /* Recursive loop 104 */
        /* Pre code */
        for (int j218 = 0; j218 < 4; j218 = j218 + 1) {
            fRec96_tmp[j218] = fRec96_perm[j218];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec96[i] =
                fZec55[i] - fConst372 * (fConst373 * fRec96[i - 2] + fConst374 * fRec96[i - 1]);
        }
        /* Post code */
        for (int j219 = 0; j219 < 4; j219 = j219 + 1) {
            fRec96_perm[j219] = fRec96_tmp[vsize + j219];
        }
        /* Recursive loop 105 */
        /* Pre code */
        for (int j220 = 0; j220 < 4; j220 = j220 + 1) {
            fRec95_tmp[j220] = fRec95_perm[j220];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec95[i] = fConst372 * (fConst376 * fRec96[i] + fConst377 * fRec96[i - 1] +
                                     fConst376 * fRec96[i - 2]) -
                        fConst378 * (fConst379 * fRec95[i - 2] + fConst380 * fRec95[i - 1]);
        }
        /* Post code */
        for (int j221 = 0; j221 < 4; j221 = j221 + 1) {
            fRec95_perm[j221] = fRec95_tmp[vsize + j221];
        }
        /* Recursive loop 106 */
        /* Pre code */
        for (int j222 = 0; j222 < 4; j222 = j222 + 1) {
            fRec94_tmp[j222] = fRec94_perm[j222];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec94[i] = fConst378 * (fConst381 * fRec95[i] + fConst382 * fRec95[i - 1] +
                                     fConst381 * fRec95[i - 2]) -
                        fConst383 * (fConst384 * fRec94[i - 2] + fConst385 * fRec94[i - 1]);
        }
        /* Post code */
        for (int j223 = 0; j223 < 4; j223 = j223 + 1) {
            fRec94_perm[j223] = fRec94_tmp[vsize + j223];
        }
        /* Vectorizable loop 107 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec56[i] = fConst383 * (fConst386 * fRec94[i] + fConst387 * fRec94[i - 1] +
                                     fConst386 * fRec94[i - 2]);
        }
        /* Recursive loop 108 */
        /* Pre code */
        for (int j232 = 0; j232 < 4; j232 = j232 + 1) {
            fRec103_tmp[j232] = fRec103_perm[j232];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec103[i] =
                fZec56[i] - fConst410 * (fConst411 * fRec103[i - 2] + fConst412 * fRec103[i - 1]);
        }
        /* Post code */
        for (int j233 = 0; j233 < 4; j233 = j233 + 1) {
            fRec103_perm[j233] = fRec103_tmp[vsize + j233];
        }
        /* Recursive loop 109 */
        /* Pre code */
        for (int j234 = 0; j234 < 4; j234 = j234 + 1) {
            fRec102_tmp[j234] = fRec102_perm[j234];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec102[i] = fConst410 * (fConst414 * fRec103[i] + fConst415 * fRec103[i - 1] +
                                      fConst414 * fRec103[i - 2]) -
                         fConst416 * (fConst417 * fRec102[i - 2] + fConst418 * fRec102[i - 1]);
        }
        /* Post code */
        for (int j235 = 0; j235 < 4; j235 = j235 + 1) {
            fRec102_perm[j235] = fRec102_tmp[vsize + j235];
        }
        /* Recursive loop 110 */
        /* Pre code */
        for (int j236 = 0; j236 < 4; j236 = j236 + 1) {
            fRec101_tmp[j236] = fRec101_perm[j236];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec101[i] = fConst416 * (fConst419 * fRec102[i] + fConst420 * fRec102[i - 1] +
                                      fConst419 * fRec102[i - 2]) -
                         fConst421 * (fConst422 * fRec101[i - 2] + fConst423 * fRec101[i - 1]);
        }
        /* Post code */
        for (int j237 = 0; j237 < 4; j237 = j237 + 1) {
            fRec101_perm[j237] = fRec101_tmp[vsize + j237];
        }
        /* Vectorizable loop 111 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec57[i] = fConst421 * (fConst424 * fRec101[i] + fConst425 * fRec101[i - 1] +
                                     fConst424 * fRec101[i - 2]);
        }
        /* Recursive loop 112 */
        /* Pre code */
        for (int j246 = 0; j246 < 4; j246 = j246 + 1) {
            fRec110_tmp[j246] = fRec110_perm[j246];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec110[i] =
                fZec57[i] - fConst448 * (fConst449 * fRec110[i - 2] + fConst450 * fRec110[i - 1]);
        }
        /* Post code */
        for (int j247 = 0; j247 < 4; j247 = j247 + 1) {
            fRec110_perm[j247] = fRec110_tmp[vsize + j247];
        }
        /* Recursive loop 113 */
        /* Pre code */
        for (int j248 = 0; j248 < 4; j248 = j248 + 1) {
            fRec109_tmp[j248] = fRec109_perm[j248];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec109[i] = fConst448 * (fConst452 * fRec110[i] + fConst453 * fRec110[i - 1] +
                                      fConst452 * fRec110[i - 2]) -
                         fConst454 * (fConst455 * fRec109[i - 2] + fConst456 * fRec109[i - 1]);
        }
        /* Post code */
        for (int j249 = 0; j249 < 4; j249 = j249 + 1) {
            fRec109_perm[j249] = fRec109_tmp[vsize + j249];
        }
        /* Recursive loop 114 */
        /* Pre code */
        for (int j250 = 0; j250 < 4; j250 = j250 + 1) {
            fRec108_tmp[j250] = fRec108_perm[j250];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec108[i] = fConst454 * (fConst457 * fRec109[i] + fConst458 * fRec109[i - 1] +
                                      fConst457 * fRec109[i - 2]) -
                         fConst459 * (fConst460 * fRec108[i - 2] + fConst461 * fRec108[i - 1]);
        }
        /* Post code */
        for (int j251 = 0; j251 < 4; j251 = j251 + 1) {
            fRec108_perm[j251] = fRec108_tmp[vsize + j251];
        }
        /* Vectorizable loop 115 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec58[i] = fConst459 * (fConst462 * fRec108[i] + fConst463 * fRec108[i - 1] +
                                     fConst462 * fRec108[i - 2]);
        }
        /* Recursive loop 116 */
        /* Pre code */
        for (int j260 = 0; j260 < 4; j260 = j260 + 1) {
            fRec117_tmp[j260] = fRec117_perm[j260];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec117[i] =
                fZec58[i] - fConst486 * (fConst487 * fRec117[i - 2] + fConst488 * fRec117[i - 1]);
        }
        /* Post code */
        for (int j261 = 0; j261 < 4; j261 = j261 + 1) {
            fRec117_perm[j261] = fRec117_tmp[vsize + j261];
        }
        /* Recursive loop 117 */
        /* Pre code */
        for (int j262 = 0; j262 < 4; j262 = j262 + 1) {
            fRec116_tmp[j262] = fRec116_perm[j262];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec116[i] = fConst486 * (fConst490 * fRec117[i] + fConst491 * fRec117[i - 1] +
                                      fConst490 * fRec117[i - 2]) -
                         fConst492 * (fConst493 * fRec116[i - 2] + fConst494 * fRec116[i - 1]);
        }
        /* Post code */
        for (int j263 = 0; j263 < 4; j263 = j263 + 1) {
            fRec116_perm[j263] = fRec116_tmp[vsize + j263];
        }
        /* Recursive loop 118 */
        /* Pre code */
        for (int j264 = 0; j264 < 4; j264 = j264 + 1) {
            fRec115_tmp[j264] = fRec115_perm[j264];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec115[i] = fConst492 * (fConst495 * fRec116[i] + fConst496 * fRec116[i - 1] +
                                      fConst495 * fRec116[i - 2]) -
                         fConst497 * (fConst498 * fRec115[i - 2] + fConst499 * fRec115[i - 1]);
        }
        /* Post code */
        for (int j265 = 0; j265 < 4; j265 = j265 + 1) {
            fRec115_perm[j265] = fRec115_tmp[vsize + j265];
        }
        /* Vectorizable loop 119 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fZec59[i] = fConst497 * (fConst500 * fRec115[i] + fConst501 * fRec115[i - 1] +
                                     fConst500 * fRec115[i - 2]);
        }
        /* Recursive loop 120 */
        /* Pre code */
        for (int j84 = 0; j84 < 4; j84 = j84 + 1) {
            fRec26_tmp[j84] = fRec26_perm[j84];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec26[i] = fZec46[i] - fConst9 * (fConst10 * fRec26[i - 2] + fConst13 * fRec26[i - 1]);
        }
        /* Post code */
        for (int j85 = 0; j85 < 4; j85 = j85 + 1) {
            fRec26_perm[j85] = fRec26_tmp[vsize + j85];
        }
        /* Recursive loop 121 */
        /* Pre code */
        for (int j98 = 0; j98 < 4; j98 = j98 + 1) {
            fRec30_tmp[j98] = fRec30_perm[j98];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec30[i] =
                fZec47[i] - fConst48 * (fConst49 * fRec30[i - 2] + fConst52 * fRec30[i - 1]);
        }
        /* Post code */
        for (int j99 = 0; j99 < 4; j99 = j99 + 1) {
            fRec30_perm[j99] = fRec30_tmp[vsize + j99];
        }
        /* Recursive loop 122 */
        /* Pre code */
        for (int j112 = 0; j112 < 4; j112 = j112 + 1) {
            fRec37_tmp[j112] = fRec37_perm[j112];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec37[i] =
                fZec48[i] - fConst86 * (fConst87 * fRec37[i - 2] + fConst90 * fRec37[i - 1]);
        }
        /* Post code */
        for (int j113 = 0; j113 < 4; j113 = j113 + 1) {
            fRec37_perm[j113] = fRec37_tmp[vsize + j113];
        }
        /* Recursive loop 123 */
        /* Pre code */
        for (int j126 = 0; j126 < 4; j126 = j126 + 1) {
            fRec44_tmp[j126] = fRec44_perm[j126];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec44[i] =
                fZec49[i] - fConst124 * (fConst125 * fRec44[i - 2] + fConst128 * fRec44[i - 1]);
        }
        /* Post code */
        for (int j127 = 0; j127 < 4; j127 = j127 + 1) {
            fRec44_perm[j127] = fRec44_tmp[vsize + j127];
        }
        /* Recursive loop 124 */
        /* Pre code */
        for (int j140 = 0; j140 < 4; j140 = j140 + 1) {
            fRec51_tmp[j140] = fRec51_perm[j140];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec51[i] =
                fZec50[i] - fConst162 * (fConst163 * fRec51[i - 2] + fConst166 * fRec51[i - 1]);
        }
        /* Post code */
        for (int j141 = 0; j141 < 4; j141 = j141 + 1) {
            fRec51_perm[j141] = fRec51_tmp[vsize + j141];
        }
        /* Recursive loop 125 */
        /* Pre code */
        for (int j154 = 0; j154 < 4; j154 = j154 + 1) {
            fRec58_tmp[j154] = fRec58_perm[j154];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec58[i] =
                fZec51[i] - fConst200 * (fConst201 * fRec58[i - 2] + fConst204 * fRec58[i - 1]);
        }
        /* Post code */
        for (int j155 = 0; j155 < 4; j155 = j155 + 1) {
            fRec58_perm[j155] = fRec58_tmp[vsize + j155];
        }
        /* Recursive loop 126 */
        /* Pre code */
        for (int j168 = 0; j168 < 4; j168 = j168 + 1) {
            fRec65_tmp[j168] = fRec65_perm[j168];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec65[i] =
                fZec52[i] - fConst238 * (fConst239 * fRec65[i - 2] + fConst242 * fRec65[i - 1]);
        }
        /* Post code */
        for (int j169 = 0; j169 < 4; j169 = j169 + 1) {
            fRec65_perm[j169] = fRec65_tmp[vsize + j169];
        }
        /* Recursive loop 127 */
        /* Pre code */
        for (int j182 = 0; j182 < 4; j182 = j182 + 1) {
            fRec72_tmp[j182] = fRec72_perm[j182];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec72[i] =
                fZec53[i] - fConst276 * (fConst277 * fRec72[i - 2] + fConst280 * fRec72[i - 1]);
        }
        /* Post code */
        for (int j183 = 0; j183 < 4; j183 = j183 + 1) {
            fRec72_perm[j183] = fRec72_tmp[vsize + j183];
        }
        /* Recursive loop 128 */
        /* Pre code */
        for (int j196 = 0; j196 < 4; j196 = j196 + 1) {
            fRec79_tmp[j196] = fRec79_perm[j196];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec79[i] =
                fZec54[i] - fConst314 * (fConst315 * fRec79[i - 2] + fConst318 * fRec79[i - 1]);
        }
        /* Post code */
        for (int j197 = 0; j197 < 4; j197 = j197 + 1) {
            fRec79_perm[j197] = fRec79_tmp[vsize + j197];
        }
        /* Recursive loop 129 */
        /* Pre code */
        for (int j210 = 0; j210 < 4; j210 = j210 + 1) {
            fRec86_tmp[j210] = fRec86_perm[j210];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec86[i] =
                fZec55[i] - fConst352 * (fConst353 * fRec86[i - 2] + fConst356 * fRec86[i - 1]);
        }
        /* Post code */
        for (int j211 = 0; j211 < 4; j211 = j211 + 1) {
            fRec86_perm[j211] = fRec86_tmp[vsize + j211];
        }
        /* Recursive loop 130 */
        /* Pre code */
        for (int j224 = 0; j224 < 4; j224 = j224 + 1) {
            fRec93_tmp[j224] = fRec93_perm[j224];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec93[i] =
                fZec56[i] - fConst390 * (fConst391 * fRec93[i - 2] + fConst394 * fRec93[i - 1]);
        }
        /* Post code */
        for (int j225 = 0; j225 < 4; j225 = j225 + 1) {
            fRec93_perm[j225] = fRec93_tmp[vsize + j225];
        }
        /* Recursive loop 131 */
        /* Pre code */
        for (int j238 = 0; j238 < 4; j238 = j238 + 1) {
            fRec100_tmp[j238] = fRec100_perm[j238];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec100[i] =
                fZec57[i] - fConst428 * (fConst429 * fRec100[i - 2] + fConst432 * fRec100[i - 1]);
        }
        /* Post code */
        for (int j239 = 0; j239 < 4; j239 = j239 + 1) {
            fRec100_perm[j239] = fRec100_tmp[vsize + j239];
        }
        /* Recursive loop 132 */
        /* Pre code */
        for (int j252 = 0; j252 < 4; j252 = j252 + 1) {
            fRec107_tmp[j252] = fRec107_perm[j252];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec107[i] =
                fZec58[i] - fConst466 * (fConst467 * fRec107[i - 2] + fConst470 * fRec107[i - 1]);
        }
        /* Post code */
        for (int j253 = 0; j253 < 4; j253 = j253 + 1) {
            fRec107_perm[j253] = fRec107_tmp[vsize + j253];
        }
        /* Recursive loop 133 */
        /* Pre code */
        for (int j266 = 0; j266 < 4; j266 = j266 + 1) {
            fRec114_tmp[j266] = fRec114_perm[j266];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec114[i] =
                fZec59[i] - fConst504 * (fConst505 * fRec114[i - 2] + fConst508 * fRec114[i - 1]);
        }
        /* Post code */
        for (int j267 = 0; j267 < 4; j267 = j267 + 1) {
            fRec114_perm[j267] = fRec114_tmp[vsize + j267];
        }
        /* Recursive loop 134 */
        /* Pre code */
        for (int j274 = 0; j274 < 4; j274 = j274 + 1) {
            fRec121_tmp[j274] = fRec121_perm[j274];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec121[i] =
                fZec59[i] - fConst524 * (fConst525 * fRec121[i - 2] + fConst526 * fRec121[i - 1]);
        }
        /* Post code */
        for (int j275 = 0; j275 < 4; j275 = j275 + 1) {
            fRec121_perm[j275] = fRec121_tmp[vsize + j275];
        }
        /* Recursive loop 135 */
        /* Pre code */
        for (int j86 = 0; j86 < 4; j86 = j86 + 1) {
            fRec25_tmp[j86] = fRec25_perm[j86];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec25[i] = fConst9 * (fConst15 * fRec26[i] + fConst16 * fRec26[i - 1] +
                                   fConst15 * fRec26[i - 2]) -
                        fConst17 * (fConst18 * fRec25[i - 2] + fConst19 * fRec25[i - 1]);
        }
        /* Post code */
        for (int j87 = 0; j87 < 4; j87 = j87 + 1) {
            fRec25_perm[j87] = fRec25_tmp[vsize + j87];
        }
        /* Recursive loop 136 */
        /* Pre code */
        for (int j100 = 0; j100 < 4; j100 = j100 + 1) {
            fRec29_tmp[j100] = fRec29_perm[j100];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec29[i] = fConst48 * (fConst54 * fRec30[i] + fConst55 * fRec30[i - 1] +
                                    fConst54 * fRec30[i - 2]) -
                        fConst56 * (fConst57 * fRec29[i - 2] + fConst58 * fRec29[i - 1]);
        }
        /* Post code */
        for (int j101 = 0; j101 < 4; j101 = j101 + 1) {
            fRec29_perm[j101] = fRec29_tmp[vsize + j101];
        }
        /* Recursive loop 137 */
        /* Pre code */
        for (int j114 = 0; j114 < 4; j114 = j114 + 1) {
            fRec36_tmp[j114] = fRec36_perm[j114];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec36[i] = fConst86 * (fConst92 * fRec37[i] + fConst93 * fRec37[i - 1] +
                                    fConst92 * fRec37[i - 2]) -
                        fConst94 * (fConst95 * fRec36[i - 2] + fConst96 * fRec36[i - 1]);
        }
        /* Post code */
        for (int j115 = 0; j115 < 4; j115 = j115 + 1) {
            fRec36_perm[j115] = fRec36_tmp[vsize + j115];
        }
        /* Recursive loop 138 */
        /* Pre code */
        for (int j128 = 0; j128 < 4; j128 = j128 + 1) {
            fRec43_tmp[j128] = fRec43_perm[j128];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec43[i] = fConst124 * (fConst130 * fRec44[i] + fConst131 * fRec44[i - 1] +
                                     fConst130 * fRec44[i - 2]) -
                        fConst132 * (fConst133 * fRec43[i - 2] + fConst134 * fRec43[i - 1]);
        }
        /* Post code */
        for (int j129 = 0; j129 < 4; j129 = j129 + 1) {
            fRec43_perm[j129] = fRec43_tmp[vsize + j129];
        }
        /* Recursive loop 139 */
        /* Pre code */
        for (int j142 = 0; j142 < 4; j142 = j142 + 1) {
            fRec50_tmp[j142] = fRec50_perm[j142];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec50[i] = fConst162 * (fConst168 * fRec51[i] + fConst169 * fRec51[i - 1] +
                                     fConst168 * fRec51[i - 2]) -
                        fConst170 * (fConst171 * fRec50[i - 2] + fConst172 * fRec50[i - 1]);
        }
        /* Post code */
        for (int j143 = 0; j143 < 4; j143 = j143 + 1) {
            fRec50_perm[j143] = fRec50_tmp[vsize + j143];
        }
        /* Recursive loop 140 */
        /* Pre code */
        for (int j156 = 0; j156 < 4; j156 = j156 + 1) {
            fRec57_tmp[j156] = fRec57_perm[j156];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec57[i] = fConst200 * (fConst206 * fRec58[i] + fConst207 * fRec58[i - 1] +
                                     fConst206 * fRec58[i - 2]) -
                        fConst208 * (fConst209 * fRec57[i - 2] + fConst210 * fRec57[i - 1]);
        }
        /* Post code */
        for (int j157 = 0; j157 < 4; j157 = j157 + 1) {
            fRec57_perm[j157] = fRec57_tmp[vsize + j157];
        }
        /* Recursive loop 141 */
        /* Pre code */
        for (int j170 = 0; j170 < 4; j170 = j170 + 1) {
            fRec64_tmp[j170] = fRec64_perm[j170];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec64[i] = fConst238 * (fConst244 * fRec65[i] + fConst245 * fRec65[i - 1] +
                                     fConst244 * fRec65[i - 2]) -
                        fConst246 * (fConst247 * fRec64[i - 2] + fConst248 * fRec64[i - 1]);
        }
        /* Post code */
        for (int j171 = 0; j171 < 4; j171 = j171 + 1) {
            fRec64_perm[j171] = fRec64_tmp[vsize + j171];
        }
        /* Recursive loop 142 */
        /* Pre code */
        for (int j184 = 0; j184 < 4; j184 = j184 + 1) {
            fRec71_tmp[j184] = fRec71_perm[j184];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec71[i] = fConst276 * (fConst282 * fRec72[i] + fConst283 * fRec72[i - 1] +
                                     fConst282 * fRec72[i - 2]) -
                        fConst284 * (fConst285 * fRec71[i - 2] + fConst286 * fRec71[i - 1]);
        }
        /* Post code */
        for (int j185 = 0; j185 < 4; j185 = j185 + 1) {
            fRec71_perm[j185] = fRec71_tmp[vsize + j185];
        }
        /* Recursive loop 143 */
        /* Pre code */
        for (int j198 = 0; j198 < 4; j198 = j198 + 1) {
            fRec78_tmp[j198] = fRec78_perm[j198];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec78[i] = fConst314 * (fConst320 * fRec79[i] + fConst321 * fRec79[i - 1] +
                                     fConst320 * fRec79[i - 2]) -
                        fConst322 * (fConst323 * fRec78[i - 2] + fConst324 * fRec78[i - 1]);
        }
        /* Post code */
        for (int j199 = 0; j199 < 4; j199 = j199 + 1) {
            fRec78_perm[j199] = fRec78_tmp[vsize + j199];
        }
        /* Recursive loop 144 */
        /* Pre code */
        for (int j212 = 0; j212 < 4; j212 = j212 + 1) {
            fRec85_tmp[j212] = fRec85_perm[j212];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec85[i] = fConst352 * (fConst358 * fRec86[i] + fConst359 * fRec86[i - 1] +
                                     fConst358 * fRec86[i - 2]) -
                        fConst360 * (fConst361 * fRec85[i - 2] + fConst362 * fRec85[i - 1]);
        }
        /* Post code */
        for (int j213 = 0; j213 < 4; j213 = j213 + 1) {
            fRec85_perm[j213] = fRec85_tmp[vsize + j213];
        }
        /* Recursive loop 145 */
        /* Pre code */
        for (int j226 = 0; j226 < 4; j226 = j226 + 1) {
            fRec92_tmp[j226] = fRec92_perm[j226];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec92[i] = fConst390 * (fConst396 * fRec93[i] + fConst397 * fRec93[i - 1] +
                                     fConst396 * fRec93[i - 2]) -
                        fConst398 * (fConst399 * fRec92[i - 2] + fConst400 * fRec92[i - 1]);
        }
        /* Post code */
        for (int j227 = 0; j227 < 4; j227 = j227 + 1) {
            fRec92_perm[j227] = fRec92_tmp[vsize + j227];
        }
        /* Recursive loop 146 */
        /* Pre code */
        for (int j240 = 0; j240 < 4; j240 = j240 + 1) {
            fRec99_tmp[j240] = fRec99_perm[j240];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec99[i] = fConst428 * (fConst434 * fRec100[i] + fConst435 * fRec100[i - 1] +
                                     fConst434 * fRec100[i - 2]) -
                        fConst436 * (fConst437 * fRec99[i - 2] + fConst438 * fRec99[i - 1]);
        }
        /* Post code */
        for (int j241 = 0; j241 < 4; j241 = j241 + 1) {
            fRec99_perm[j241] = fRec99_tmp[vsize + j241];
        }
        /* Recursive loop 147 */
        /* Pre code */
        for (int j254 = 0; j254 < 4; j254 = j254 + 1) {
            fRec106_tmp[j254] = fRec106_perm[j254];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec106[i] = fConst466 * (fConst472 * fRec107[i] + fConst473 * fRec107[i - 1] +
                                      fConst472 * fRec107[i - 2]) -
                         fConst474 * (fConst475 * fRec106[i - 2] + fConst476 * fRec106[i - 1]);
        }
        /* Post code */
        for (int j255 = 0; j255 < 4; j255 = j255 + 1) {
            fRec106_perm[j255] = fRec106_tmp[vsize + j255];
        }
        /* Recursive loop 148 */
        /* Pre code */
        for (int j268 = 0; j268 < 4; j268 = j268 + 1) {
            fRec113_tmp[j268] = fRec113_perm[j268];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec113[i] = fConst504 * (fConst510 * fRec114[i] + fConst511 * fRec114[i - 1] +
                                      fConst510 * fRec114[i - 2]) -
                         fConst512 * (fConst513 * fRec113[i - 2] + fConst514 * fRec113[i - 1]);
        }
        /* Post code */
        for (int j269 = 0; j269 < 4; j269 = j269 + 1) {
            fRec113_perm[j269] = fRec113_tmp[vsize + j269];
        }
        /* Recursive loop 149 */
        /* Pre code */
        for (int j276 = 0; j276 < 4; j276 = j276 + 1) {
            fRec120_tmp[j276] = fRec120_perm[j276];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec120[i] = fConst524 * (fConst528 * fRec121[i] + fConst529 * fRec121[i - 1] +
                                      fConst528 * fRec121[i - 2]) -
                         fConst530 * (fConst531 * fRec120[i - 2] + fConst532 * fRec120[i - 1]);
        }
        /* Post code */
        for (int j277 = 0; j277 < 4; j277 = j277 + 1) {
            fRec120_perm[j277] = fRec120_tmp[vsize + j277];
        }
        /* Recursive loop 150 */
        /* Pre code */
        for (int j88 = 0; j88 < 4; j88 = j88 + 1) {
            fRec24_tmp[j88] = fRec24_perm[j88];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec24[i] = fConst17 * (fConst21 * fRec25[i] + fConst22 * fRec25[i - 1] +
                                    fConst21 * fRec25[i - 2]) -
                        fConst23 * (fConst24 * fRec24[i - 2] + fConst25 * fRec24[i - 1]);
        }
        /* Post code */
        for (int j89 = 0; j89 < 4; j89 = j89 + 1) {
            fRec24_perm[j89] = fRec24_tmp[vsize + j89];
        }
        /* Recursive loop 151 */
        /* Pre code */
        for (int j102 = 0; j102 < 4; j102 = j102 + 1) {
            fRec28_tmp[j102] = fRec28_perm[j102];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec28[i] = fConst56 * (fConst60 * fRec29[i] + fConst61 * fRec29[i - 1] +
                                    fConst60 * fRec29[i - 2]) -
                        fConst62 * (fConst63 * fRec28[i - 2] + fConst64 * fRec28[i - 1]);
        }
        /* Post code */
        for (int j103 = 0; j103 < 4; j103 = j103 + 1) {
            fRec28_perm[j103] = fRec28_tmp[vsize + j103];
        }
        /* Recursive loop 152 */
        /* Pre code */
        for (int j116 = 0; j116 < 4; j116 = j116 + 1) {
            fRec35_tmp[j116] = fRec35_perm[j116];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec35[i] = fConst94 * (fConst98 * fRec36[i] + fConst99 * fRec36[i - 1] +
                                    fConst98 * fRec36[i - 2]) -
                        fConst100 * (fConst101 * fRec35[i - 2] + fConst102 * fRec35[i - 1]);
        }
        /* Post code */
        for (int j117 = 0; j117 < 4; j117 = j117 + 1) {
            fRec35_perm[j117] = fRec35_tmp[vsize + j117];
        }
        /* Recursive loop 153 */
        /* Pre code */
        for (int j130 = 0; j130 < 4; j130 = j130 + 1) {
            fRec42_tmp[j130] = fRec42_perm[j130];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec42[i] = fConst132 * (fConst136 * fRec43[i] + fConst137 * fRec43[i - 1] +
                                     fConst136 * fRec43[i - 2]) -
                        fConst138 * (fConst139 * fRec42[i - 2] + fConst140 * fRec42[i - 1]);
        }
        /* Post code */
        for (int j131 = 0; j131 < 4; j131 = j131 + 1) {
            fRec42_perm[j131] = fRec42_tmp[vsize + j131];
        }
        /* Recursive loop 154 */
        /* Pre code */
        for (int j144 = 0; j144 < 4; j144 = j144 + 1) {
            fRec49_tmp[j144] = fRec49_perm[j144];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec49[i] = fConst170 * (fConst174 * fRec50[i] + fConst175 * fRec50[i - 1] +
                                     fConst174 * fRec50[i - 2]) -
                        fConst176 * (fConst177 * fRec49[i - 2] + fConst178 * fRec49[i - 1]);
        }
        /* Post code */
        for (int j145 = 0; j145 < 4; j145 = j145 + 1) {
            fRec49_perm[j145] = fRec49_tmp[vsize + j145];
        }
        /* Recursive loop 155 */
        /* Pre code */
        for (int j158 = 0; j158 < 4; j158 = j158 + 1) {
            fRec56_tmp[j158] = fRec56_perm[j158];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec56[i] = fConst208 * (fConst212 * fRec57[i] + fConst213 * fRec57[i - 1] +
                                     fConst212 * fRec57[i - 2]) -
                        fConst214 * (fConst215 * fRec56[i - 2] + fConst216 * fRec56[i - 1]);
        }
        /* Post code */
        for (int j159 = 0; j159 < 4; j159 = j159 + 1) {
            fRec56_perm[j159] = fRec56_tmp[vsize + j159];
        }
        /* Recursive loop 156 */
        /* Pre code */
        for (int j172 = 0; j172 < 4; j172 = j172 + 1) {
            fRec63_tmp[j172] = fRec63_perm[j172];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec63[i] = fConst246 * (fConst250 * fRec64[i] + fConst251 * fRec64[i - 1] +
                                     fConst250 * fRec64[i - 2]) -
                        fConst252 * (fConst253 * fRec63[i - 2] + fConst254 * fRec63[i - 1]);
        }
        /* Post code */
        for (int j173 = 0; j173 < 4; j173 = j173 + 1) {
            fRec63_perm[j173] = fRec63_tmp[vsize + j173];
        }
        /* Recursive loop 157 */
        /* Pre code */
        for (int j186 = 0; j186 < 4; j186 = j186 + 1) {
            fRec70_tmp[j186] = fRec70_perm[j186];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec70[i] = fConst284 * (fConst288 * fRec71[i] + fConst289 * fRec71[i - 1] +
                                     fConst288 * fRec71[i - 2]) -
                        fConst290 * (fConst291 * fRec70[i - 2] + fConst292 * fRec70[i - 1]);
        }
        /* Post code */
        for (int j187 = 0; j187 < 4; j187 = j187 + 1) {
            fRec70_perm[j187] = fRec70_tmp[vsize + j187];
        }
        /* Recursive loop 158 */
        /* Pre code */
        for (int j200 = 0; j200 < 4; j200 = j200 + 1) {
            fRec77_tmp[j200] = fRec77_perm[j200];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec77[i] = fConst322 * (fConst326 * fRec78[i] + fConst327 * fRec78[i - 1] +
                                     fConst326 * fRec78[i - 2]) -
                        fConst328 * (fConst329 * fRec77[i - 2] + fConst330 * fRec77[i - 1]);
        }
        /* Post code */
        for (int j201 = 0; j201 < 4; j201 = j201 + 1) {
            fRec77_perm[j201] = fRec77_tmp[vsize + j201];
        }
        /* Recursive loop 159 */
        /* Pre code */
        for (int j214 = 0; j214 < 4; j214 = j214 + 1) {
            fRec84_tmp[j214] = fRec84_perm[j214];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec84[i] = fConst360 * (fConst364 * fRec85[i] + fConst365 * fRec85[i - 1] +
                                     fConst364 * fRec85[i - 2]) -
                        fConst366 * (fConst367 * fRec84[i - 2] + fConst368 * fRec84[i - 1]);
        }
        /* Post code */
        for (int j215 = 0; j215 < 4; j215 = j215 + 1) {
            fRec84_perm[j215] = fRec84_tmp[vsize + j215];
        }
        /* Recursive loop 160 */
        /* Pre code */
        for (int j228 = 0; j228 < 4; j228 = j228 + 1) {
            fRec91_tmp[j228] = fRec91_perm[j228];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec91[i] = fConst398 * (fConst402 * fRec92[i] + fConst403 * fRec92[i - 1] +
                                     fConst402 * fRec92[i - 2]) -
                        fConst404 * (fConst405 * fRec91[i - 2] + fConst406 * fRec91[i - 1]);
        }
        /* Post code */
        for (int j229 = 0; j229 < 4; j229 = j229 + 1) {
            fRec91_perm[j229] = fRec91_tmp[vsize + j229];
        }
        /* Recursive loop 161 */
        /* Pre code */
        for (int j242 = 0; j242 < 4; j242 = j242 + 1) {
            fRec98_tmp[j242] = fRec98_perm[j242];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec98[i] = fConst436 * (fConst440 * fRec99[i] + fConst441 * fRec99[i - 1] +
                                     fConst440 * fRec99[i - 2]) -
                        fConst442 * (fConst443 * fRec98[i - 2] + fConst444 * fRec98[i - 1]);
        }
        /* Post code */
        for (int j243 = 0; j243 < 4; j243 = j243 + 1) {
            fRec98_perm[j243] = fRec98_tmp[vsize + j243];
        }
        /* Recursive loop 162 */
        /* Pre code */
        for (int j256 = 0; j256 < 4; j256 = j256 + 1) {
            fRec105_tmp[j256] = fRec105_perm[j256];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec105[i] = fConst474 * (fConst478 * fRec106[i] + fConst479 * fRec106[i - 1] +
                                      fConst478 * fRec106[i - 2]) -
                         fConst480 * (fConst481 * fRec105[i - 2] + fConst482 * fRec105[i - 1]);
        }
        /* Post code */
        for (int j257 = 0; j257 < 4; j257 = j257 + 1) {
            fRec105_perm[j257] = fRec105_tmp[vsize + j257];
        }
        /* Recursive loop 163 */
        /* Pre code */
        for (int j270 = 0; j270 < 4; j270 = j270 + 1) {
            fRec112_tmp[j270] = fRec112_perm[j270];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec112[i] = fConst512 * (fConst516 * fRec113[i] + fConst517 * fRec113[i - 1] +
                                      fConst516 * fRec113[i - 2]) -
                         fConst518 * (fConst519 * fRec112[i - 2] + fConst520 * fRec112[i - 1]);
        }
        /* Post code */
        for (int j271 = 0; j271 < 4; j271 = j271 + 1) {
            fRec112_perm[j271] = fRec112_tmp[vsize + j271];
        }
        /* Recursive loop 164 */
        /* Pre code */
        for (int j278 = 0; j278 < 4; j278 = j278 + 1) {
            fRec119_tmp[j278] = fRec119_perm[j278];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec119[i] = fConst530 * (fConst533 * fRec120[i] + fConst534 * fRec120[i - 1] +
                                      fConst533 * fRec120[i - 2]) -
                         fConst535 * (fConst536 * fRec119[i - 2] + fConst537 * fRec119[i - 1]);
        }
        /* Post code */
        for (int j279 = 0; j279 < 4; j279 = j279 + 1) {
            fRec119_perm[j279] = fRec119_tmp[vsize + j279];
        }
        /* Recursive loop 165 */
        /* Pre code */
        for (int j90 = 0; j90 < 4; j90 = j90 + 1) {
            fRec23_tmp[j90] = fRec23_perm[j90];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec23[i] = fRec23[i - 1] * fSlow44 +
                        std::fabs(fConst23 * (fConst28 * fRec24[i] + fConst29 * fRec24[i - 1] +
                                              fConst28 * fRec24[i - 2])) *
                            fSlow45;
        }
        /* Post code */
        for (int j91 = 0; j91 < 4; j91 = j91 + 1) {
            fRec23_perm[j91] = fRec23_tmp[vsize + j91];
        }
        /* Recursive loop 166 */
        /* Pre code */
        for (int j104 = 0; j104 < 4; j104 = j104 + 1) {
            fRec27_tmp[j104] = fRec27_perm[j104];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec27[i] =
                fSlow44 * fRec27[i - 1] +
                fSlow45 * std::fabs(fConst62 * (fConst66 * fRec28[i] + fConst67 * fRec28[i - 1] +
                                                fConst66 * fRec28[i - 2]));
        }
        /* Post code */
        for (int j105 = 0; j105 < 4; j105 = j105 + 1) {
            fRec27_perm[j105] = fRec27_tmp[vsize + j105];
        }
        /* Recursive loop 167 */
        /* Pre code */
        for (int j118 = 0; j118 < 4; j118 = j118 + 1) {
            fRec34_tmp[j118] = fRec34_perm[j118];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec34[i] =
                fSlow44 * fRec34[i - 1] +
                fSlow45 * std::fabs(fConst100 * (fConst104 * fRec35[i] + fConst105 * fRec35[i - 1] +
                                                 fConst104 * fRec35[i - 2]));
        }
        /* Post code */
        for (int j119 = 0; j119 < 4; j119 = j119 + 1) {
            fRec34_perm[j119] = fRec34_tmp[vsize + j119];
        }
        /* Recursive loop 168 */
        /* Pre code */
        for (int j132 = 0; j132 < 4; j132 = j132 + 1) {
            fRec41_tmp[j132] = fRec41_perm[j132];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec41[i] =
                fSlow44 * fRec41[i - 1] +
                fSlow45 * std::fabs(fConst138 * (fConst142 * fRec42[i] + fConst143 * fRec42[i - 1] +
                                                 fConst142 * fRec42[i - 2]));
        }
        /* Post code */
        for (int j133 = 0; j133 < 4; j133 = j133 + 1) {
            fRec41_perm[j133] = fRec41_tmp[vsize + j133];
        }
        /* Recursive loop 169 */
        /* Pre code */
        for (int j146 = 0; j146 < 4; j146 = j146 + 1) {
            fRec48_tmp[j146] = fRec48_perm[j146];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec48[i] =
                fSlow44 * fRec48[i - 1] +
                fSlow45 * std::fabs(fConst176 * (fConst180 * fRec49[i] + fConst181 * fRec49[i - 1] +
                                                 fConst180 * fRec49[i - 2]));
        }
        /* Post code */
        for (int j147 = 0; j147 < 4; j147 = j147 + 1) {
            fRec48_perm[j147] = fRec48_tmp[vsize + j147];
        }
        /* Recursive loop 170 */
        /* Pre code */
        for (int j160 = 0; j160 < 4; j160 = j160 + 1) {
            fRec55_tmp[j160] = fRec55_perm[j160];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec55[i] =
                fSlow44 * fRec55[i - 1] +
                fSlow45 * std::fabs(fConst214 * (fConst218 * fRec56[i] + fConst219 * fRec56[i - 1] +
                                                 fConst218 * fRec56[i - 2]));
        }
        /* Post code */
        for (int j161 = 0; j161 < 4; j161 = j161 + 1) {
            fRec55_perm[j161] = fRec55_tmp[vsize + j161];
        }
        /* Recursive loop 171 */
        /* Pre code */
        for (int j174 = 0; j174 < 4; j174 = j174 + 1) {
            fRec62_tmp[j174] = fRec62_perm[j174];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec62[i] =
                fSlow44 * fRec62[i - 1] +
                fSlow45 * std::fabs(fConst252 * (fConst256 * fRec63[i] + fConst257 * fRec63[i - 1] +
                                                 fConst256 * fRec63[i - 2]));
        }
        /* Post code */
        for (int j175 = 0; j175 < 4; j175 = j175 + 1) {
            fRec62_perm[j175] = fRec62_tmp[vsize + j175];
        }
        /* Recursive loop 172 */
        /* Pre code */
        for (int j188 = 0; j188 < 4; j188 = j188 + 1) {
            fRec69_tmp[j188] = fRec69_perm[j188];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec69[i] =
                fSlow44 * fRec69[i - 1] +
                fSlow45 * std::fabs(fConst290 * (fConst294 * fRec70[i] + fConst295 * fRec70[i - 1] +
                                                 fConst294 * fRec70[i - 2]));
        }
        /* Post code */
        for (int j189 = 0; j189 < 4; j189 = j189 + 1) {
            fRec69_perm[j189] = fRec69_tmp[vsize + j189];
        }
        /* Recursive loop 173 */
        /* Pre code */
        for (int j202 = 0; j202 < 4; j202 = j202 + 1) {
            fRec76_tmp[j202] = fRec76_perm[j202];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec76[i] =
                fSlow44 * fRec76[i - 1] +
                fSlow45 * std::fabs(fConst328 * (fConst332 * fRec77[i] + fConst333 * fRec77[i - 1] +
                                                 fConst332 * fRec77[i - 2]));
        }
        /* Post code */
        for (int j203 = 0; j203 < 4; j203 = j203 + 1) {
            fRec76_perm[j203] = fRec76_tmp[vsize + j203];
        }
        /* Recursive loop 174 */
        /* Pre code */
        for (int j216 = 0; j216 < 4; j216 = j216 + 1) {
            fRec83_tmp[j216] = fRec83_perm[j216];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec83[i] =
                fSlow44 * fRec83[i - 1] +
                fSlow45 * std::fabs(fConst366 * (fConst370 * fRec84[i] + fConst371 * fRec84[i - 1] +
                                                 fConst370 * fRec84[i - 2]));
        }
        /* Post code */
        for (int j217 = 0; j217 < 4; j217 = j217 + 1) {
            fRec83_perm[j217] = fRec83_tmp[vsize + j217];
        }
        /* Recursive loop 175 */
        /* Pre code */
        for (int j230 = 0; j230 < 4; j230 = j230 + 1) {
            fRec90_tmp[j230] = fRec90_perm[j230];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec90[i] =
                fSlow44 * fRec90[i - 1] +
                fSlow45 * std::fabs(fConst404 * (fConst408 * fRec91[i] + fConst409 * fRec91[i - 1] +
                                                 fConst408 * fRec91[i - 2]));
        }
        /* Post code */
        for (int j231 = 0; j231 < 4; j231 = j231 + 1) {
            fRec90_perm[j231] = fRec90_tmp[vsize + j231];
        }
        /* Recursive loop 176 */
        /* Pre code */
        for (int j244 = 0; j244 < 4; j244 = j244 + 1) {
            fRec97_tmp[j244] = fRec97_perm[j244];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec97[i] =
                fSlow44 * fRec97[i - 1] +
                fSlow45 * std::fabs(fConst442 * (fConst446 * fRec98[i] + fConst447 * fRec98[i - 1] +
                                                 fConst446 * fRec98[i - 2]));
        }
        /* Post code */
        for (int j245 = 0; j245 < 4; j245 = j245 + 1) {
            fRec97_perm[j245] = fRec97_tmp[vsize + j245];
        }
        /* Recursive loop 177 */
        /* Pre code */
        for (int j258 = 0; j258 < 4; j258 = j258 + 1) {
            fRec104_tmp[j258] = fRec104_perm[j258];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec104[i] = fSlow44 * fRec104[i - 1] +
                         fSlow45 * std::fabs(fConst480 *
                                             (fConst484 * fRec105[i] + fConst485 * fRec105[i - 1] +
                                              fConst484 * fRec105[i - 2]));
        }
        /* Post code */
        for (int j259 = 0; j259 < 4; j259 = j259 + 1) {
            fRec104_perm[j259] = fRec104_tmp[vsize + j259];
        }
        /* Recursive loop 178 */
        /* Pre code */
        for (int j272 = 0; j272 < 4; j272 = j272 + 1) {
            fRec111_tmp[j272] = fRec111_perm[j272];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec111[i] = fSlow44 * fRec111[i - 1] +
                         fSlow45 * std::fabs(fConst518 *
                                             (fConst522 * fRec112[i] + fConst523 * fRec112[i - 1] +
                                              fConst522 * fRec112[i - 2]));
        }
        /* Post code */
        for (int j273 = 0; j273 < 4; j273 = j273 + 1) {
            fRec111_perm[j273] = fRec111_tmp[vsize + j273];
        }
        /* Recursive loop 179 */
        /* Pre code */
        for (int j280 = 0; j280 < 4; j280 = j280 + 1) {
            fRec118_tmp[j280] = fRec118_perm[j280];
        }
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fRec118[i] = fSlow44 * fRec118[i - 1] +
                         fSlow45 * std::fabs(fConst535 *
                                             (fConst538 * fRec119[i] + fConst539 * fRec119[i - 1] +
                                              fConst538 * fRec119[i - 2]));
        }
        /* Post code */
        for (int j281 = 0; j281 < 4; j281 = j281 + 1) {
            fRec118_perm[j281] = fRec118_tmp[vsize + j281];
        }
        /* Vectorizable loop 180 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            fVbargraph0  = static_cast<FAUSTFLOAT>(fSlow46 + 2e+01 * std::log10(fRec23[i]));
            fVbargraph1  = static_cast<FAUSTFLOAT>(fSlow46 + 2e+01 * std::log10(fRec27[i]));
            fVbargraph2  = static_cast<FAUSTFLOAT>(fSlow46 + 2e+01 * std::log10(fRec34[i]));
            fVbargraph3  = static_cast<FAUSTFLOAT>(fSlow46 + 2e+01 * std::log10(fRec41[i]));
            fVbargraph4  = static_cast<FAUSTFLOAT>(fSlow46 + 2e+01 * std::log10(fRec48[i]));
            fVbargraph5  = static_cast<FAUSTFLOAT>(fSlow46 + 2e+01 * std::log10(fRec55[i]));
            fVbargraph6  = static_cast<FAUSTFLOAT>(fSlow46 + 2e+01 * std::log10(fRec62[i]));
            fVbargraph7  = static_cast<FAUSTFLOAT>(fSlow46 + 2e+01 * std::log10(fRec69[i]));
            fVbargraph8  = static_cast<FAUSTFLOAT>(fSlow46 + 2e+01 * std::log10(fRec76[i]));
            fVbargraph9  = static_cast<FAUSTFLOAT>(fSlow46 + 2e+01 * std::log10(fRec83[i]));
            fVbargraph10 = static_cast<FAUSTFLOAT>(fSlow46 + 2e+01 * std::log10(fRec90[i]));
            fVbargraph11 = static_cast<FAUSTFLOAT>(fSlow46 + 2e+01 * std::log10(fRec97[i]));
            fVbargraph12 = static_cast<FAUSTFLOAT>(fSlow46 + 2e+01 * std::log10(fRec104[i]));
            fVbargraph13 = static_cast<FAUSTFLOAT>(fSlow46 + 2e+01 * std::log10(fRec111[i]));
            fVbargraph14 = static_cast<FAUSTFLOAT>(fSlow46 + 2e+01 * std::log10(fRec118[i]));
            output0[i]   = static_cast<FAUSTFLOAT>(fZec44[i]);
        }
        /* Vectorizable loop 181 */
        /* Compute code */
        for (int i = 0; i < vsize; i = i + 1) {
            output1[i] = static_cast<FAUSTFLOAT>(fZec45[i]);
        }
    }
}
