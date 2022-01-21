#include <bits/stdc++.h>

using namespace std;

int main() {

    FILE* file;
    file = fopen("alu.bin", "wb");
    int stage;
    cin >> stage;
    for (int i = 0; i < (int) pow(2, 13 + stage) ; ++i) {
        int A = i & 0xf;
        int B = (i >> 4) & 0xf;
        int Cin = (i >> 8) & 1;
        int SRI = (i >> 5) & 0x10;
        int OP = (i >> 10) & 0xf;
        int Zin = (i >> 9) & 0x20;
        int F = 0;
        int Cout;
        switch(OP){
            case 0: F = A + B + (stage == 2 ? Cin : 0); break;
            case 1: F = A - B - (stage == 2 ? Cin : 0); break;
            case 2: F = A + (stage == 2 ? Cin : 1); break;
            case 3: F = A - (stage == 2 ? Cin : 1); break;
            case 4: F = A & B | (stage == 2 ? SRI : 0); break;
            case 5: F = A | B | (stage == 2 ? SRI : 0); break;
            case 6: F = A ^ B | (stage == 2 ? SRI : 0); break;
            case 7: F = (~A & 0xf) | (stage == 2 ? SRI : 0); break;
            case 8: F = A | (stage == 2 ? SRI : 0); break;
            case 9: F = B | (stage == 2 ? SRI : 0); break;
            case 10: F = (A << 1) | Cin; break;
            case 11: F = (A | SRI) >> 1; if (stage == 1) Cin = A & 1; Cout = Cin << 4; F = F | Cout; break;
            default: break;
        }
        int Zout = F & 0x0f;
        Zout = (Zout ? 0 : 0x20);
        Zout = (stage == 2 ? Zout & Zin : Zout);
        F = F & 0x1f;;
        F = F | Zout;
        char *x = new char;
        *x = F;
        fwrite(x, sizeof(char), 1, file);
    }
    fclose(file);
    return 0;
}

