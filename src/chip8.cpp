#include "chip8.hpp"


unsigned char chip8_fontset[80] =
{
    0xF0, 0x90, 0x90, 0x90, 0xF0, //0
    0x20, 0x60, 0x20, 0x20, 0x70, //1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, //2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, //3
    0x90, 0x90, 0xF0, 0x10, 0x10, //4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, //5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, //6
    0xF0, 0x10, 0x20, 0x40, 0x40, //7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, //8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, //9
    0xF0, 0x90, 0xF0, 0x90, 0x90, //A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, //B
    0xF0, 0x80, 0x80, 0x80, 0xF0, //C
    0xE0, 0x90, 0x90, 0x90, 0xE0, //D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, //E
    0xF0, 0x80, 0xF0, 0x80, 0x80  //F
};

Chip8::Chip8() {
    init();

    if (!audioManager.init()) { 
        std::cerr << "Audio initialization failed!" << std::endl;
    }
}

void Chip8::init() {
    std::memset(memory, 0, sizeof(memory));

    std::memset(V, 0, sizeof(V));

    I = 0;

    pc = 0x200;

    opcode = 0;

    std::memcpy(memory, chip8_fontset, sizeof(chip8_fontset));

    delayTimer = 0;
    soundTimer = 0;

    std::memset(stack, 0, sizeof(stack));
    sp = 0;

    std::memset(gfx, 1, sizeof(gfx));


    std::memset(key, 0, sizeof(key));
}

void Chip8::loadRom(const char* filename) {
    std::ifstream romFile(filename, std::ios::binary);

    if (!romFile) {
        std::cerr << "Failed to open ROM: " << filename << std::endl;
        return;
    }


    romFile.seekg(0, std::ios::end); 
    romSize = romFile.tellg(); 
    romFile.seekg(0, std::ios::beg); 

    if (romSize > (4096 - 0x200)) {
        std::cerr << "ROM size (" << romSize << " bytes) exceeds available memory!" << std::endl;
        romFile.close();
        return;
    }

    romFile.read(reinterpret_cast<char*>(&memory[0x200]), romSize);

    if (!romFile) {
        std::cerr << "Error reading ROM: " << filename << std::endl;
    } else {
        std::cout << "Successfully loaded ROM: " << filename << std::endl;
        std::cout << "Loaded ROM size: " << romSize << " bytes." << std::endl;

    }

    romFile.close();
    romLoaded = true;
}

void Chip8::emulateCycle() {

    opcode = memory[pc] << 8 | memory[pc + 1]; 

    switch(opcode & 0xF000){


        // 0x0000 (Contains CLEAR & RETURN)

        case 0x0000:

            switch (opcode & 0x000F) {
                // 00E0 - Clear screen
                case CLEAR_DISPLAY:
                    memset(gfx, 0, sizeof(gfx));
                    drawFlag = true;
                    pc+=2;
                    break;

                // 00EE - Return from subroutine
                case RET:
                    --sp;
                    pc = stack[sp];
                    pc += 2;
                    break;
            }
            break;

        // 1NNN
        case JMP:
            pc = opcode & 0x0FFF;
            break;

        // 2NNN
        case CALL:
            stack[sp] = pc;
            ++sp;
            pc = opcode & 0x0FFF;
            break;

        // 3XNN
        case SE_VX_BYTE:
            if (V[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF))
                pc += 4;
            else
                pc += 2;
            break;

        // 4XNN
        case SNE_VX_BYTE:
            if (V[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF))
                pc += 4;
            else
                pc += 2;
            break;

        // 5XY0
        case SE_VX_VY:
            if (V[(opcode & 0x0F00) >> 8] == V[(opcode & 0x00F0) >> 4])
                pc += 4;
            else
                pc += 2;
            break;

        // 6XNN 
        case LD_VX_BYTE:
            V[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
            pc += 2;
            break;

        // 7XNN
        case ADD_VX_BYTE:
            V[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
            pc += 2;
            break;

        // 8XY?
        case 0x8000:
            switch (opcode & 0x000F) {

                // 8XY0
                case LD_VX_VY:
                    V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4];
                    pc += 2;
                    break;

                // 8XY1
                case OR_VX_VY:
                    V[(opcode & 0x0F00) >> 8] |= V[(opcode & 0x00F0) >> 4];
                    pc += 2;
                    break;

                // 8XY2
                case AND_VX_VY:
                    V[(opcode & 0x0F00) >> 8] &= V[(opcode & 0x00F0) >> 4];
                    pc += 2;
                    break;

                // 8XY3
                case XOR_VX_VY:
                    V[(opcode & 0x0F00) >> 8] ^= V[(opcode & 0x00F0) >> 4];
                    pc += 2;
                    break;

                // 8XY4
                case ADD_VX_VY:
                    V[(opcode & 0x0F00) >> 8] += V[(opcode & 0x00F0) >> 4];
                    if(V[(opcode & 0x00F0) >> 4] > (0xFF - V[(opcode & 0x0F00) >> 8]))
                        V[0xF] = 1; //carry
                    else
                        V[0xF] = 0;
                    pc += 2;
                    break;

                // 8XY5
                case SUB_VX_VY:
                    if(V[(opcode & 0x00F0) >> 4] > V[(opcode & 0x0F00) >> 8])
                        V[0xF] = 0; 
                    else
                        V[0xF] = 1;
                    V[(opcode & 0x0F00) >> 8] -= V[(opcode & 0x00F0) >> 4];
                    pc += 2;
                    break;

                // 0x8XY6
                case SHR_VX:
                    V[0xF] = V[(opcode & 0x0F00) >> 8] & 0x1;
                    V[(opcode & 0x0F00) >> 8] >>= 1;
                    pc += 2;
                    break;

                // 0x8XY7
                case SUBN_VX_VY:
                    if(V[(opcode & 0x0F00) >> 8] > V[(opcode & 0x00F0) >> 4])   
                        V[0xF] = 0; 
                    else
                        V[0xF] = 1;
                    V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4] - V[(opcode & 0x0F00) >> 8];
                    pc += 2;
                    break;

                // 0x8XYE
                case SHL_VX:
                    V[0xF] = V[(opcode & 0x0F00) >> 8] >> 7;
                    V[(opcode & 0x0F00) >> 8] <<= 1;
                    pc += 2;
                    break;

            }
            break;

        // 9XY0 
        case SNE_VX_VY:
            if (V[(opcode & 0x0F00) >> 8] != V[(opcode & 0x00F0) >> 4])
                pc += 4;
            else
                pc += 2;
            break;

        // ANNN 
        case LD_I:
            I = opcode & 0x0FFF;
            pc += 2;
            break;

        // BNNN
        case JP_V0:
            pc = (opcode & 0x0FFF) + V[0];
            break;


        // CNNN
        case RND_VX_BYTE:
            V[(opcode & 0x0F00) >> 8] = (rand() % (0xFF + 1)) & (opcode & 0x00FF);
            pc += 2;
            break;

        // DXYN
        case DRW_VX_VY_N:
        {
            unsigned short x = V[(opcode & 0x0F00) >> 8];
            unsigned short y = V[(opcode & 0x00F0) >> 4];
            unsigned short height = opcode & 0x000F;
            unsigned short pixel;

            V[0xF] = 0;
            for (int yline = 0; yline < height; yline++)
            {
                pixel = memory[I + yline];
                for(int xline = 0; xline < 8; xline++)
                {
                    if((pixel & (0x80 >> xline)) != 0)
                    {
                        if(gfx[(x + xline + ((y + yline) * 64))] == 1)
                        {
                            V[0xF] = 1;
                        }
                        gfx[x + xline + ((y + yline) * 64)] ^= 1;
                    }
                }
            }

            drawFlag = true;
            pc += 2;
        }
            break;

        // EX??
        case 0xE000:

            switch (opcode & 0x00FF) {

                // EX9E
                case SKP_VX:
                    if (key[V[(opcode & 0x0F00) >> 8]] != 0)
                        pc +=  4;
                    else
                        pc += 2;
                    break;

                // EXA1
                case SKNP_VX:
                    if (key[V[(opcode & 0x0F00) >> 8]] == 0)
                        pc +=  4;
                    else
                        pc += 2;
                    break;
            }
            break;

        // FX??
        case 0xF000:
            switch(opcode & 0x00FF)
            {
                // FX07
                case LD_VX_DT:
                    V[(opcode & 0x0F00) >> 8] = delayTimer;
                    pc += 2;
                    break;

                // FX0A
                case LD_VX_K:
                {
                    bool keyPressed = false;

                    for(int i = 0; i < 16; ++i)
                    {
                        if(key[i] != 0)
                        {
                            V[(opcode & 0x0F00) >> 8] = i;
                            keyPressed = true;
                        }
                    }

                    if(!keyPressed)
                        return;

                    pc += 2;
                }
                    break;

                // FX15
                case LD_DT_VX:
                    delayTimer = V[(opcode & 0x0F00) >> 8];
                    pc += 2;
                    break;

                // FX18
                case LD_ST_VX:
                    soundTimer = V[(opcode & 0x0F00) >> 8];
                    pc += 2;
                    break;

                // FX1E
                case ADD_I_VX:
                    if(I + V[(opcode & 0x0F00) >> 8] > 0xFFF)
                        V[0xF] = 1;
                    else
                        V[0xF] = 0;
                    I += V[(opcode & 0x0F00) >> 8];
                    pc += 2;
                    break;

                // FX29
                case LD_F_VX:
                    I = V[(opcode & 0x0F00) >> 8] * 0x5;
                    pc += 2;
                    break;

                // FX33
                case LD_B_VX:
                    memory[I] = V[(opcode & 0x0F00) >> 8] / 100;
                    memory[I + 1] = (V[(opcode & 0x0F00) >> 8] / 10) % 10;
                    memory[I + 2] = V[(opcode & 0x0F00) >> 8] % 10;
                    pc += 2;
                    break;

                // FX55
                case LD_I_VX:
                    for (int i = 0; i <= ((opcode & 0x0F00) >> 8); ++i)
                        memory[I + i] = V[i];

                    I += ((opcode & 0x0F00) >> 8) + 1;
                    pc += 2;
                    break;

                // FX65
                case LD_VX_I:
                    for (int i = 0; i <= ((opcode & 0x0F00) >> 8); ++i)
                        V[i] = memory[I + i];

                    I += ((opcode & 0x0F00) >> 8) + 1;
                    pc += 2;
                    break;


            }
            break;

        default:
            printf("\nUnknown op code: %.4X\n", opcode);
            exit(3);
    }


    if (delayTimer > 0)
        --delayTimer;

    if (soundTimer > 0) {
        if (soundTimer == 1) {
            audioManager.playSound(); 
        }
        --soundTimer;
    } else {
        audioManager.stopSound();  
    }


    // Update game pixels
    for (int i = 0; i < 2048; ++i) {
        uint8_t pixel = gfx[i];
        gamePixels[i] = (0x00FFFFFF * pixel) | 0xFF000000;
    }
}

void Chip8::cleanUp() {
    audioManager.cleanUp();
    SDL_Quit();
}
