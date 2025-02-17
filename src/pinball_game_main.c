#include "global.h"
#include "agb_sram.h"
#include "main.h"
#include "m4a.h"
#include "constants/ereader.h"
#include "constants/fields.h"

extern struct PinballGame gUnknown_02000000;

typedef void (*VoidFunc)(void);

struct Unk20028D8
{
    void (*unk0)(void);
    void (*unk4)(void);
};

extern struct Unk20028D8 gUnknown_020028D8[9];

extern const struct Unk20028D8 gUnknown_086B077C[];
extern const VoidFunc gUnknown_086B085C[];
extern const struct MainUnk44 gUnknown_086B02CC[];
extern const struct MainUnk44 gUnknown_086B03BC[];

void sub_1D4D0(void);
void sub_356A0(void);
void sub_3ADA0(void);
void sub_3E5D0(void);
void sub_467F4(void);
void sub_4A6A0(void);
void sub_47110(void);
static void sub_4A270(void);
void sub_4A518(void);
void sub_4A90C(void);
void sub_4B280(void);
void sub_4B334(void);
void sub_4B408(s16);
void sub_4B654(void);
void sub_4B678(u16);

extern const StateFunc gPinballGameStateFuncs[];
extern const u8 gUnknown_08137E14[][0x20];
extern const u8 gUnknown_084C0C6C[];


void PinballGameMain(void)
{
    gPinballGameStateFuncs[gMain.subState]();
}

void sub_49ED4(void)
{
    s16 i, j;
    s16 numRngAdvances;
    s16 var0;

    numRngAdvances = gMain.systemFrameCount % 16;
    for (i = 0; i < numRngAdvances; i++)
        Random();

    sub_10C0();
    gCurrentPinballGame = &gUnknown_02000000;
    ResetSomeGraphicsRelatedStuff();
    gMain.unkE = 0;
    if (gMain.unkD)
        var0 = 0;
    else if (gMain.unk5 == gMain.selectedField)
        var0 = 1;
    else if (gMain.selectedField <= FIELD_SAPPHIRE)
        var0 = 2;
    else
        var0 = 3;

    switch (var0)
    {
    case 0:
        sub_4A270();
        sub_4A518();
        sub_467F4();
        DmaCopy16(3, gUnknown_02031520.unk2C, (void *)OBJ_PLTT, OBJ_PLTT_SIZE);
        if (gMain.eReaderBonuses[EREADER_DX_MODE_CARD])
            DmaCopy16(3, &gUnknown_08137E14[gCurrentPinballGame->unk5F6], (void *)OBJ_PLTT + 0x20, 0x20);

        sub_4A90C();
        for (i = 0; i < 9; i++)
            gUnknown_020028D8[i].unk0();

        m4aMPlayAllStop();
        sub_47110();
        sub_4A518();
        if (gMain.mainState == STATE_GAME_IDLE)
            sub_4B678(2);
        else
            sub_4B678(1);

        sub_4A270();
        sub_4A90C();
        gUnknown_086B085C[gMain.unk6]();
        if (gMain.selectedField == FIELD_RUBY || gMain.selectedField == FIELD_SAPPHIRE)
            sub_1D4D0();
        else if (gMain.selectedField == FIELD_2)
            sub_356A0();
        else if (gMain.selectedField == FIELD_4)
            sub_3ADA0();
        else if (gMain.selectedField == FIELD_5)
            sub_3E5D0();
        break;
    case 1:
        sub_4A270();
        sub_4A518();
        sub_467F4();
        DmaCopy16(3, gUnknown_02031520.unk2C, (void *)OBJ_PLTT, OBJ_PLTT_SIZE);
        if (gMain.eReaderBonuses[EREADER_DX_MODE_CARD])
            DmaCopy16(3, &gUnknown_08137E14[gCurrentPinballGame->unk5F6], (void *)OBJ_PLTT + 0x20, 0x20);

        sub_4A90C();
        for (i = 0; i < 9; i++)
            gUnknown_020028D8[i].unk0();

        sub_47110();
        break;
    case 2:
        sub_4A270();
        sub_4A6A0();
        sub_4B678(0);
        sub_4A90C();
        gUnknown_086B085C[gMain.unk6]();
        if (gMain.selectedField == FIELD_RUBY)
            sub_46FD4(1);

        sub_1C7F4(0, 0);
        gCurrentPinballGame->unk6C4 = 0;
        break;
    case 3:
        sub_4A270();
        sub_4A518();
        sub_467F4();
        DmaCopy16(3, gUnknown_02031520.unk2C, (void *)OBJ_PLTT, OBJ_PLTT_SIZE);
        sub_4A90C();
        for (i = 0; i < 9; i++)
            gUnknown_020028D8[i].unk0();

        sub_47110();
        break;
    }

    gUnknown_02031520.unk8 = 0;
    for (j = 0; j < NUM_SPECIES; j++)
    {
        if (gMain_saveData.pokedexFlags[j] > 3)
            gUnknown_02031520.unk8++;
    }

    sub_0CBC();
    sub_024C();
    gCurrentPinballGame->unk1100 = 0;
    gMain.unk36 = 1;

    switch (var0)
    {
    case 0:
        if (gMain.mainState != STATE_GAME_IDLE && gCurrentPinballGame->unkF4C && gMPlayInfo_BGM.status < 0)
            MPlayStart(&gMPlayInfo_BGM, gCurrentPinballGame->unkF4C);
        if (gMain.selectedField <= FIELD_SAPPHIRE)
            sub_31BE8(gCurrentPinballGame->unk6F);
        break;
    case 1:
    case 2:
        gMain.blendControl = 0xCE;
        gMain.blendBrightness = 0;
        break;
    case 3:
        break;
    }

    gMain.subState++;
}

static void sub_4A270(void)
{
    REG_DISPCNT = DISPCNT_MODE_0 | DISPCNT_OBJ_1D_MAP | DISPCNT_FORCED_BLANK | DISPCNT_OBJ_ON;
    switch (gMain.selectedField)
    {
    case FIELD_RUBY:
        REG_BG3CNT = BGCNT_TXT256x512 | BGCNT_MOSAIC | BGCNT_SCREENBASE(0) | BGCNT_CHARBASE(2) | BGCNT_PRIORITY(3);
        REG_DISPCNT |= DISPCNT_BG3_ON;
        REG_BG2CNT = BGCNT_TXT256x512 | BGCNT_MOSAIC | BGCNT_SCREENBASE(2) | BGCNT_CHARBASE(1) | BGCNT_PRIORITY(2);
        REG_DISPCNT |= DISPCNT_BG2_ON;
        REG_BG1CNT = BGCNT_TXT256x512 | BGCNT_MOSAIC | BGCNT_SCREENBASE(6) | BGCNT_CHARBASE(2) | BGCNT_PRIORITY(1);
        REG_DISPCNT |= DISPCNT_BG1_ON;
        REG_BG0CNT = BGCNT_TXT256x512 | BGCNT_SCREENBASE(4) | BGCNT_CHARBASE(1) | BGCNT_PRIORITY(0); 
        REG_DISPCNT |= DISPCNT_BG0_ON;
        break;
    case FIELD_SAPPHIRE:
        REG_BG3CNT = BGCNT_TXT256x512 | BGCNT_MOSAIC | BGCNT_SCREENBASE(0) | BGCNT_CHARBASE(2) | BGCNT_PRIORITY(3);
        REG_DISPCNT |= DISPCNT_BG3_ON;
        REG_BG2CNT = BGCNT_TXT256x512 | BGCNT_MOSAIC | BGCNT_SCREENBASE(2) | BGCNT_CHARBASE(1) | BGCNT_PRIORITY(2);
        REG_DISPCNT |= DISPCNT_BG2_ON;
        REG_BG1CNT = BGCNT_TXT256x512 | BGCNT_MOSAIC | BGCNT_SCREENBASE(6) | BGCNT_CHARBASE(2) | BGCNT_PRIORITY(1);
        REG_DISPCNT |= DISPCNT_BG1_ON;
        REG_BG0CNT = BGCNT_TXT256x512 | BGCNT_SCREENBASE(4) | BGCNT_CHARBASE(1) | BGCNT_PRIORITY(0);
        REG_DISPCNT |= DISPCNT_BG0_ON;
        break;
    case FIELD_2:
        REG_BG3CNT = BGCNT_TXT256x256 | BGCNT_SCREENBASE(0) | BGCNT_CHARBASE(2) | BGCNT_PRIORITY(3);
        REG_DISPCNT |= DISPCNT_BG3_ON;
        REG_BG2CNT = BGCNT_TXT256x256 | BGCNT_SCREENBASE(1) | BGCNT_CHARBASE(2) | BGCNT_PRIORITY(2);
        REG_DISPCNT |= DISPCNT_BG2_ON;
        REG_BG1CNT = BGCNT_TXT256x256 | BGCNT_SCREENBASE(2) | BGCNT_CHARBASE(2) | BGCNT_PRIORITY(0);
        REG_DISPCNT |= DISPCNT_BG1_ON;
        REG_BG0CNT = BGCNT_TXT256x512 | BGCNT_SCREENBASE(4) | BGCNT_CHARBASE(1) | BGCNT_PRIORITY(0);
        REG_DISPCNT |= DISPCNT_BG0_ON;
        break;
    case FIELD_3:
        REG_BG3CNT = BGCNT_TXT256x256 | BGCNT_SCREENBASE(0) | BGCNT_CHARBASE(2) | BGCNT_PRIORITY(3);
        REG_DISPCNT |= DISPCNT_BG3_ON;
        REG_BG2CNT = BGCNT_TXT256x256 | BGCNT_SCREENBASE(1) | BGCNT_CHARBASE(2) | BGCNT_PRIORITY(2);
        REG_DISPCNT |= DISPCNT_BG2_ON;
        REG_BG1CNT = BGCNT_TXT256x256 | BGCNT_SCREENBASE(2) | BGCNT_CHARBASE(2) | BGCNT_PRIORITY(1);
        REG_DISPCNT |= DISPCNT_BG1_ON;
        REG_BG0CNT = BGCNT_TXT256x512 | BGCNT_SCREENBASE(4) | BGCNT_CHARBASE(1) | BGCNT_PRIORITY(0);
        REG_DISPCNT |= DISPCNT_BG0_ON;
        break;
    case FIELD_4:
        REG_BG3CNT = BGCNT_TXT256x256 | BGCNT_SCREENBASE(0) | BGCNT_CHARBASE(2) | BGCNT_PRIORITY(3);
        REG_DISPCNT |= DISPCNT_BG3_ON;
        REG_BG2CNT = BGCNT_TXT256x256 | BGCNT_SCREENBASE(1) | BGCNT_CHARBASE(2) | BGCNT_PRIORITY(2);
        REG_DISPCNT |= DISPCNT_BG2_ON;
        REG_BG0CNT = BGCNT_TXT256x512 | BGCNT_SCREENBASE(4) | BGCNT_CHARBASE(1) | BGCNT_PRIORITY(0);
        REG_DISPCNT |= DISPCNT_BG0_ON;
        break;
    case FIELD_5:
        REG_BG3CNT = BGCNT_TXT256x256 | BGCNT_SCREENBASE(0) | BGCNT_CHARBASE(2) | BGCNT_PRIORITY(3);
        REG_DISPCNT |= DISPCNT_BG3_ON;
        REG_BG2CNT = BGCNT_TXT256x256 | BGCNT_SCREENBASE(1) | BGCNT_CHARBASE(2) | BGCNT_PRIORITY(2);
        REG_DISPCNT |= DISPCNT_BG2_ON;
        REG_BG0CNT = BGCNT_TXT256x512 | BGCNT_SCREENBASE(4) | BGCNT_CHARBASE(1) | BGCNT_PRIORITY(0);
        REG_DISPCNT |= DISPCNT_BG0_ON;
        break;
    case FIELD_6:
        REG_BG3CNT = BGCNT_TXT256x512 | BGCNT_SCREENBASE(0) | BGCNT_CHARBASE(2) | BGCNT_PRIORITY(3);
        REG_DISPCNT |= DISPCNT_BG3_ON;
        REG_BG2CNT = BGCNT_TXT256x512 | BGCNT_SCREENBASE(2) | BGCNT_CHARBASE(2) | BGCNT_PRIORITY(2);
        REG_DISPCNT |= DISPCNT_BG2_ON;
        REG_BG1CNT = BGCNT_TXT256x512 | BGCNT_SCREENBASE(6) | BGCNT_CHARBASE(2) | BGCNT_PRIORITY(1);
        REG_DISPCNT |= DISPCNT_BG1_ON;
        REG_BG0CNT = BGCNT_TXT256x512 | BGCNT_SCREENBASE(4) | BGCNT_CHARBASE(1) | BGCNT_PRIORITY(0);
        REG_DISPCNT |= DISPCNT_BG0_ON;
        break;
    case FIELD_7:
        REG_BG3CNT = BGCNT_TXT256x256 | BGCNT_SCREENBASE(0) | BGCNT_CHARBASE(2) | BGCNT_PRIORITY(3);
        REG_DISPCNT |= DISPCNT_BG3_ON;
        REG_BG2CNT = BGCNT_TXT256x256 | BGCNT_SCREENBASE(1) | BGCNT_CHARBASE(2) | BGCNT_PRIORITY(2);
        REG_DISPCNT |= DISPCNT_BG2_ON;
        REG_BG1CNT = BGCNT_TXT256x512 | BGCNT_SCREENBASE(2) | BGCNT_CHARBASE(2) | BGCNT_PRIORITY(0);
        REG_DISPCNT |= DISPCNT_BG1_ON;
        REG_BG0CNT = BGCNT_TXT256x512 | BGCNT_SCREENBASE(4) | BGCNT_CHARBASE(1) | BGCNT_PRIORITY(0);
        REG_DISPCNT |= DISPCNT_BG0_ON;
        break;
    }

    gMain.unk16 = REG_DISPCNT;
    REG_MOSAIC = 0;
}

void sub_4A518(void)
{
    gMain.unkF = 0;
    gMain.unk10 = 0;
    gMain.fieldFrameCount = 0;
    gMain.unk11 = 0;
    gMain.unk12 = 0;
    gMain.unk14 = 0;
    gMain.vCount = 144;
    gMain.unk28 = 0;
    gMain.unk2A = 0;
    gMain.unk36 = 0;
    gMain.blendControl = 0;
    gMain.blendAlpha = 0;
    gMain.blendBrightness = 0;
    if (gMain.unk5 == gMain.selectedField)
    {
        DmaFill16(3, 0, gCurrentPinballGame, sizeof(struct PinballGame));
        if (gMain.eReaderBonuses[EREADER_DX_MODE_CARD])
        {
            gCurrentPinballGame->unk1C6 = 168;
            gCurrentPinballGame->unk1C8 = 168;
            gCurrentPinballGame->unk1CC = 13;
            gCurrentPinballGame->unk1CA = 13;
            gCurrentPinballGame->unk1D0 = 0;
            gCurrentPinballGame->unk1D4 = 0;
            gCurrentPinballGame->unk1D6 = 120;
            gCurrentPinballGame->unk1DC = 60;
            DmaCopy16(3, gUnknown_084C0C6C, (void *)OBJ_VRAM0 + 0x600, 0x180);
            gCurrentPinballGame->unk1E2 = 2;
            *gMain.unk44[1].unk2C = 0;
            gCurrentPinballGame->unk1C0 = 1;
            gCurrentPinballGame->unk5F6 = 3;
            gCurrentPinballGame->unk5F8 = 60 * 60;
            gCurrentPinballGame->numLives = 9;
            gCurrentPinballGame->coins = 99;
        }
        else
        {
            gCurrentPinballGame->unk1D4 = 0;
            gCurrentPinballGame->unk1D6 = -4;
            gCurrentPinballGame->numLives = 2;
            gCurrentPinballGame->coins = 10;
        }
    }

    if (gMain.mainState != STATE_GAME_IDLE)
        gCurrentPinballGame->ballSpeed = gMain_saveData.ballSpeed;

    gCurrentPinballGame->unk38 = 40000;
    gCurrentPinballGame->unk1D = 0;
    gCurrentPinballGame->unk132c = &gCurrentPinballGame->unk1334[0];
    gCurrentPinballGame->unk1330 = &gCurrentPinballGame->unk1334[0];
    gCurrentPinballGame->unk66 = 0;
}

void sub_4A6A0(void)
{
    switch (gCurrentPinballGame->unk282)
    {
    case 0:
        gCurrentPinballGame->unk132c->unk10 = 119;
        gCurrentPinballGame->unk132c->unk12 = 279;
        gCurrentPinballGame->unk132c->unk30 = 0;
        gCurrentPinballGame->unk132c->unk32 = 0;
        gCurrentPinballGame->unk132c->unk6 = 0;
        gCurrentPinballGame->unk132c->unk34 = gCurrentPinballGame->unk132c->unk10 << 8;
        gCurrentPinballGame->unk132c->unk38 = gCurrentPinballGame->unk132c->unk12 << 8;
        gCurrentPinballGame->unk132c->unkE = 128;
        gCurrentPinballGame->unk132c->unk0 = 1;
        gCurrentPinballGame->unk1F = 1;
        gCurrentPinballGame->unk730 = 0;
        gCurrentPinballGame->unk28 = 120;
        gCurrentPinballGame->unk25 = 4;
        if (gMain.selectedField == FIELD_RUBY)
            sub_1A9E8();
        else
            sub_32968();

        gCurrentPinballGame->unk4C = 0;
        gCurrentPinballGame->unk4E = 215;
        break;
    case 1:
        gCurrentPinballGame->unk132c->unk10 = 140;
        gCurrentPinballGame->unk132c->unk12 = 183;
        gCurrentPinballGame->unk132c->unk30 = 0;
        gCurrentPinballGame->unk132c->unk32 = 0;
        gCurrentPinballGame->unk132c->unk6 = 0;
        gCurrentPinballGame->unk132c->unk34 = gCurrentPinballGame->unk132c->unk10 << 8;
        gCurrentPinballGame->unk132c->unk38 = gCurrentPinballGame->unk132c->unk12 << 8;
        gCurrentPinballGame->unk132c->unkE = 128;
        gCurrentPinballGame->unk132c->unk0 = 1;
        gCurrentPinballGame->unk1F = 1;
        gCurrentPinballGame->unk730 = 0;
        gCurrentPinballGame->unk2A2 = 5;
        gCurrentPinballGame->unk4C = 0;
        gCurrentPinballGame->unk4E = 118;
        break;
    case 2:
        gCurrentPinballGame->unk132c->unk10 = -28;
        gCurrentPinballGame->unk132c->unk12 = -10;
        gCurrentPinballGame->unk132c->unk30 = 0;
        gCurrentPinballGame->unk132c->unk32 = 0;
        gCurrentPinballGame->unk132c->unk6 = 0;
        gCurrentPinballGame->unk132c->unk34 = gCurrentPinballGame->unk132c->unk10 << 8;
        gCurrentPinballGame->unk132c->unk38 = gCurrentPinballGame->unk132c->unk12 << 8;
        gCurrentPinballGame->unk132c->unkE = 128;
        gCurrentPinballGame->unk132c->unk0 = 1;
        gCurrentPinballGame->unk1F = 1;
        gCurrentPinballGame->unk730 = 0;
        gCurrentPinballGame->unk30C = 0;
        gCurrentPinballGame->unk306 = 7;
        gCurrentPinballGame->unk4C = 0;
        gCurrentPinballGame->unk4E = 0;
        break;
    }

    gCurrentPinballGame->unk5FC = 0;
    gCurrentPinballGame->unk5FE = 0;
    gCurrentPinballGame->unk5FB = 0;
    gCurrentPinballGame->unk54 = gCurrentPinballGame->unk4E << 8;
    gCurrentPinballGame->unk58 = gCurrentPinballGame->unk4C;
    gCurrentPinballGame->unk5A = gCurrentPinballGame->unk4E + gCurrentPinballGame->unk5FC;

    gMain.bgOffsets[2].xOffset = gCurrentPinballGame->unk4C;
    gMain.bgOffsets[2].yOffset = gCurrentPinballGame->unk4E;
    gMain.bgOffsets[3].xOffset = gCurrentPinballGame->unk4C;
    gMain.bgOffsets[3].yOffset = gCurrentPinballGame->unk4E;
    gMain.bgOffsets[1].xOffset = gCurrentPinballGame->unk4C;
    gMain.bgOffsets[1].yOffset = gCurrentPinballGame->unk4E;
    gMain.bgOffsets[0].yOffset = 80;

    gCurrentPinballGame->unkCC = gMain.bgOffsets[3].yOffset;
    gCurrentPinballGame->unk64 = gMain.bgOffsets[3].yOffset / 8;
}

void sub_4A90C(void)
{
    gUnknown_020028D8[1] = gUnknown_086B077C[0];
    gUnknown_020028D8[8] = gUnknown_086B077C[18];
    gUnknown_020028D8[6] = gUnknown_086B077C[15];
    switch (gMain.selectedField)
    {
    case FIELD_RUBY:
        gUnknown_020028D8[3] = gUnknown_086B077C[3];
        gUnknown_020028D8[7] = gUnknown_086B077C[16];
        gUnknown_020028D8[0] = gUnknown_086B077C[19];
        gUnknown_020028D8[4] = gUnknown_086B077C[11];
        gUnknown_020028D8[2] = gUnknown_086B077C[1];
        gUnknown_020028D8[5] = gUnknown_086B077C[13];
        gMain.unk44 = &gUnknown_086B02CC[gMain.selectedField * 2];
        break;
    case FIELD_SAPPHIRE:
        gUnknown_020028D8[3] = gUnknown_086B077C[4];
        gUnknown_020028D8[7] = gUnknown_086B077C[16];
        gUnknown_020028D8[0] = gUnknown_086B077C[20];
        gUnknown_020028D8[4] = gUnknown_086B077C[11];
        gUnknown_020028D8[2] = gUnknown_086B077C[1];
        gUnknown_020028D8[5] = gUnknown_086B077C[13];
        gMain.unk44 = &gUnknown_086B02CC[gMain.selectedField * 2];
        break;
    case FIELD_2:
        gUnknown_020028D8[3] = gUnknown_086B077C[5];
        gUnknown_020028D8[7] = gUnknown_086B077C[17];
        gUnknown_020028D8[0] = gUnknown_086B077C[21];
        gUnknown_020028D8[4] = gUnknown_086B077C[12];
        gUnknown_020028D8[2] = gUnknown_086B077C[2];
        gUnknown_020028D8[5] = gUnknown_086B077C[14];
        gMain.unk44 = &gUnknown_086B03BC[gMain.selectedField];
        break;
    case FIELD_3:
        gUnknown_020028D8[3] = gUnknown_086B077C[6];
        gUnknown_020028D8[7] = gUnknown_086B077C[17];
        gUnknown_020028D8[0] = gUnknown_086B077C[22];
        gUnknown_020028D8[4] = gUnknown_086B077C[12];
        gUnknown_020028D8[2] = gUnknown_086B077C[2];
        gUnknown_020028D8[5] = gUnknown_086B077C[14];
        gMain.unk44 = &gUnknown_086B03BC[gMain.selectedField];
        break;
    case FIELD_4:
        gUnknown_020028D8[3] = gUnknown_086B077C[7];
        gUnknown_020028D8[7] = gUnknown_086B077C[17];
        gUnknown_020028D8[0] = gUnknown_086B077C[23];
        gUnknown_020028D8[4] = gUnknown_086B077C[12];
        gUnknown_020028D8[2] = gUnknown_086B077C[2];
        gUnknown_020028D8[5] = gUnknown_086B077C[14];
        gMain.unk44 = &gUnknown_086B03BC[gMain.selectedField];
        break;
    case FIELD_5:
        gUnknown_020028D8[3] = gUnknown_086B077C[8];
        gUnknown_020028D8[7] = gUnknown_086B077C[17];
        gUnknown_020028D8[0] = gUnknown_086B077C[24];
        gUnknown_020028D8[4] = gUnknown_086B077C[12];
        gUnknown_020028D8[2] = gUnknown_086B077C[2];
        gUnknown_020028D8[5] = gUnknown_086B077C[14];
        gMain.unk44 = &gUnknown_086B03BC[gMain.selectedField];
        break;
    case FIELD_6:
        gUnknown_020028D8[3] = gUnknown_086B077C[9];
        gUnknown_020028D8[7] = gUnknown_086B077C[17];
        gUnknown_020028D8[0] = gUnknown_086B077C[25];
        gUnknown_020028D8[4] = gUnknown_086B077C[12];
        gUnknown_020028D8[2] = gUnknown_086B077C[2];
        gUnknown_020028D8[5] = gUnknown_086B077C[14];
        gMain.unk44 = &gUnknown_086B03BC[gMain.selectedField];
        break;
    case FIELD_7:
        gUnknown_020028D8[3] = gUnknown_086B077C[10];
        gUnknown_020028D8[7] = gUnknown_086B077C[17];
        gUnknown_020028D8[0] = gUnknown_086B077C[26];
        gUnknown_020028D8[4] = gUnknown_086B077C[12];
        gUnknown_020028D8[2] = gUnknown_086B077C[2];
        gUnknown_020028D8[5] = gUnknown_086B077C[14];
        gMain.unk44 = &gUnknown_086B03BC[gMain.selectedField];
        break;
    }
}

void sub_4AAD8(void)
{
    switch (gCurrentPinballGame->unk1D)
    {
    case 0:
        gCurrentPinballGame->unk1D = 1;
        gMain.unkE = 0;
        break;
    case 1:
        gUnknown_086B085C[gMain.unk6]();
        if (JOY_HELD(A_BUTTON | B_BUTTON | SELECT_BUTTON | START_BUTTON) == (A_BUTTON | B_BUTTON | SELECT_BUTTON | START_BUTTON))
            gMain.unkE = 1;

        if (gMain.unkE)
        {
            if (gMain.selectedField <= FIELD_SAPPHIRE)
            {
                sub_1D4D0();
                sub_31BE8(0);
            }
            else if (gMain.selectedField == FIELD_2)
            {
                sub_356A0();
            }
            else if (gMain.selectedField == FIELD_4)
            {
                sub_3ADA0();
            }
            else if (gMain.selectedField == FIELD_5)
            {
                sub_3E5D0();
            }

            if (gMain.unkF & 0x2)
                DmaCopy16(3, gCurrentPinballGame->unk111A, (void *)OBJ_PLTT, OBJ_PLTT_SIZE);

            gCurrentPinballGame->unk1D = 2;
            if (gMain.unkE == 2)
                sub_4B408(1);
        }
        break;
    case 2:
        gMain.subState++;
        break;
    }

    sub_11FC();
}

void sub_4ABC8(void)
{
    sub_111C();
    if (sub_1170())
    {
        sub_1198();
        gMain.subState++;
    }
}

void sub_4ABEC(void)
{
    s16 i;

    sub_4B280();
    gUnknown_020028D8[1].unk4();
    if (gMain.unkE == 0 && !(gMain.unkF & 0x2))
    {
        gUnknown_020028D8[2].unk4();
        gUnknown_020028D8[0].unk4();
        gUnknown_020028D8[3].unk4();
        gUnknown_020028D8[4].unk4();
        if (gMain.unkF)
        {
            if (!gCurrentPinballGame->unk1F)
            {
                for (i = 0; i < 4; i++)
                {
                    gCurrentPinballGame->unk1E = i;
                    gUnknown_020028D8[6].unk4();
                }
            }
        }
        else
        {
            gMain.fieldFrameCount++;
            gCurrentPinballGame->unk290++;
            if (gCurrentPinballGame->unk1F)
            {
                if (gCurrentPinballGame->unk1F != 2)
                {
                    for (i = 0; i < 4; i++)
                    {
                        gCurrentPinballGame->unk1E = i;
                        gUnknown_020028D8[5].unk4();
                    }
                }
            }
            else
            {
                for (i = 0; i < 4; i++)
                {
                    gCurrentPinballGame->unk1E = i;
                    gUnknown_020028D8[5].unk4();
                    gUnknown_020028D8[6].unk4();
                }
            }
        }

        gUnknown_020028D8[7].unk4();
        gUnknown_020028D8[8].unk4();
    }

    sub_47030();
}

void sub_4ACF0(void)
{
    s16 i;

    sub_4B334();
    gUnknown_020028D8[1].unk4();
    if (!(gMain.unkF & 0x2))
    {
        gUnknown_020028D8[2].unk4();
        gUnknown_020028D8[0].unk4();
        gUnknown_020028D8[3].unk4();
        gUnknown_020028D8[4].unk4();
        if (gMain.unkF)
        {
            if (!gCurrentPinballGame->unk1F)
            {
                for (i = 0; i < 4; i++)
                {
                    gCurrentPinballGame->unk1E = i;
                    gUnknown_020028D8[6].unk4();
                }
            }
        }
        else
        {
            gMain.fieldFrameCount++;
            gCurrentPinballGame->unk290++;
            if (gCurrentPinballGame->unk1F)
            {
                if (gCurrentPinballGame->unk1F != 2)
                {
                    for (i = 0; i < 4; i++)
                    {
                        gCurrentPinballGame->unk1E = i;
                        gUnknown_020028D8[5].unk4();
                    }
                }
            }
            else
            {
                for (i = 0; i < 4; i++)
                {
                    gCurrentPinballGame->unk1E = i;
                    gUnknown_020028D8[5].unk4();
                    gUnknown_020028D8[6].unk4();
                }
            }
        }

        gUnknown_020028D8[7].unk4();
        gUnknown_020028D8[8].unk4();
    }

    sub_47030();
    if ((gMain.systemFrameCount % 32) / 16 > 0)
    {
        for (i = 0; i < 10; i++)
            gUnknown_03005C00[0x34A + i] = 0xC156 + i;
    }
    else
    {
        for (i = 0; i < 10; i++)
            gUnknown_03005C00[0x34A + i] = 0x1FF;
    }

    DmaCopy16(3, &gUnknown_03005C00[0x340], (void *)0x6002680, 0x40);
}

void sub_4AE8C(void)
{
    s16 i;

    sub_4B280();
    gUnknown_020028D8[1].unk4();
    if (gMain.unkF & 0x2)
        return;

    gUnknown_020028D8[0].unk4();
    gUnknown_020028D8[2].unk4();
    gUnknown_020028D8[3].unk4();
    gUnknown_020028D8[4].unk4();
    if (gMain.unkF & ~0x40)
    {
        if (!gCurrentPinballGame->unk1F)
        {
            for (i = 0; i < 4; i++)
            {
                gCurrentPinballGame->unk66 = 0;
                gCurrentPinballGame->unk132c = &gCurrentPinballGame->unk1334[0];
                gCurrentPinballGame->unk1E = i;
                gUnknown_020028D8[6].unk4();
            }
        }
    }
    else
    {
        gMain.fieldFrameCount++;
        gCurrentPinballGame->unk290++;
        if (gCurrentPinballGame->unk1F)
        {
            if (gCurrentPinballGame->unk1F == 2)
            {
                gCurrentPinballGame->unk66 = 0;
                gCurrentPinballGame->unk132c = &gCurrentPinballGame->unk1334[0];
                gCurrentPinballGame->unk1E = 0;
            }
            else
            {
                for (i = 0; i < 4; i++)
                {
                    gCurrentPinballGame->unk66 = 0;
                    gCurrentPinballGame->unk132c = &gCurrentPinballGame->unk1334[0];
                    gCurrentPinballGame->unk1E = i;
                    gUnknown_020028D8[5].unk4();
                }
            }
        }
        else
        {
            for (i = 0; i < 4; i++)
            {
                gCurrentPinballGame->unk66 = 0;
                gCurrentPinballGame->unk132c = &gCurrentPinballGame->unk1334[0];
                gCurrentPinballGame->unk1E = i;
                gUnknown_020028D8[5].unk4();
                gUnknown_020028D8[6].unk4();
            }
        }
    }

    gUnknown_020028D8[7].unk4();
    gUnknown_020028D8[8].unk4();
}

void sub_4B000(void)
{
    s16 i;

    sub_4B334();
    if (!(gMain.unkF & 0x2))
    {
        gUnknown_020028D8[0].unk4();
        gUnknown_020028D8[2].unk4();
        gUnknown_020028D8[3].unk4();
        gUnknown_020028D8[4].unk4();
        if (gMain.unkF & ~0x40)
        {
            if (!gCurrentPinballGame->unk1F)
            {
                for (i = 0; i < 4; i++)
                {
                    gCurrentPinballGame->unk66 = 0;
                    gCurrentPinballGame->unk132c = &gCurrentPinballGame->unk1334[0];
                    gCurrentPinballGame->unk1E = i;
                    gUnknown_020028D8[6].unk4();
                }
            }
        }
        else
        {
            gMain.fieldFrameCount++;
            gCurrentPinballGame->unk290++;
            if (gCurrentPinballGame->unk1F)
            {
                if (gCurrentPinballGame->unk1F == 2)
                {
                    gCurrentPinballGame->unk66 = 0;
                    gCurrentPinballGame->unk132c = &gCurrentPinballGame->unk1334[0];
                    gCurrentPinballGame->unk1E = 0;
                }
                else
                {
                    for (i = 0; i < 4; i++)
                    {
                        gCurrentPinballGame->unk66 = 0;
                        gCurrentPinballGame->unk132c = &gCurrentPinballGame->unk1334[0];
                        gCurrentPinballGame->unk1E = i;
                        gUnknown_020028D8[5].unk4();
                    }
                }
            }
            else
            {
                for (i = 0; i < 4; i++)
                {
                    gCurrentPinballGame->unk66 = 0;
                    gCurrentPinballGame->unk132c = &gCurrentPinballGame->unk1334[0];
                    gCurrentPinballGame->unk1E = i;
                    gUnknown_020028D8[5].unk4();
                    gUnknown_020028D8[6].unk4();
                }
            }
        }

        gUnknown_020028D8[7].unk4();
        gUnknown_020028D8[8].unk4();
    }

    if ((gMain.systemFrameCount % 32) / 16 > 0)
    {
        for (i = 0; i < 9; i++)
            gUnknown_03005C00[0x32B + i] = 0xC156 + i;
    }
    else
    {
        for (i = 0; i < 9; i++)
            gUnknown_03005C00[0x32B + i] = 0x1FF;
    }

    DmaCopy16(3, &gUnknown_03005C00[0x320], (void *)0x6002640, 0x40);
}

void sub_4B20C(void)
{
    gMain.unk36 = 0;
    sub_02B4();
    m4aMPlayAllStop();
    sub_0D10();
    gMain.unk58 = gCurrentPinballGame->unk44;
    gMain.unk5C = gCurrentPinballGame->unk48;
    if (gMain.unkE == 2)
        sub_4B654();

    if (gMain.unkE == 0)
    {
        if (gMain.selectedField > FIELD_SAPPHIRE)
        {
            SetMainGameState(STATE_BONUS_FIELD_SELECT);
            return;
        }
        else if (gMain.eReaderBonuses[EREADER_DX_MODE_CARD] || gMain.eReaderBonuses[EREADER_RUIN_AREA_CARD])
        {
            SetMainGameState(STATE_INTRO);
            return;
        }
    }
    else
    {
        SetMainGameState(STATE_INTRO);
        return;
    }

    SetMainGameState(STATE_SCORES_MAIN);
}

void nullsub_19(void)
{
}

void sub_4B280(void)
{
    u16 i;

    for (i = 0; i < 5; i++)
    {
        gCurrentPinballGame->unk4[i] = 0;
        gCurrentPinballGame->unk9[i] = 0;
    }

    if (gMain.unkF)
        return;

    for (i =  0; i < 5; i++)
    {
        int buttonConfigKeyMask = (gMain.buttonConfigs[i][0] | gMain.buttonConfigs[i][1]) & KEYS_MASK;
        if (buttonConfigKeyMask == JOY_HELD(buttonConfigKeyMask))
        {
            if (gCurrentPinballGame->unkE[i] == 0)
                gCurrentPinballGame->unk4[i] = 1;

            gCurrentPinballGame->unkE[i] = 1;
        }
        else
        {
            if (gCurrentPinballGame->unkE[i])
                gCurrentPinballGame->unk9[i] = 1;

            gCurrentPinballGame->unkE[i] = 0;
        }
    }
}

void sub_4B334(void)
{
    u16 i;

    for (i = 0; i < 5; i++)
    {
        gCurrentPinballGame->unk4[i] = 0;
        gCurrentPinballGame->unk9[i] = 0;
    }

    if (gMain.unkF)
        return;

    if (gUnknown_02031510 < 60 * 60)
    {
        for (i =  0; i < 5; i++)
        {
            gCurrentPinballGame->unk4[i] = (gUnknown_02031520.unk10[gUnknown_02031510].unk0 >> i) & 0x1;
            gCurrentPinballGame->unk9[i] = (gUnknown_02031520.unk10[gUnknown_02031510].unk1 >> i) & 0x1;
            gCurrentPinballGame->unkE[i] = (gUnknown_02031520.unk10[gUnknown_02031510].unk2 >> i) & 0x1;
        }

        gUnknown_02031510++;
    }

    if (gCurrentPinballGame->unk4[1])
        gMain.newKeys = A_BUTTON;
}

void sub_4B408(s16 arg0)
{
    s16 i;
    u16 *var0;

    if (gMPlayInfo_BGM.status >= 0)
    {
        gCurrentPinballGame->unkF4C = gMPlayInfo_BGM.songHeader;
        m4aMPlayStop(&gMPlayInfo_BGM);
    }
    else
    {
        gCurrentPinballGame->unkF4C = NULL;
    }

    for (i = 0; i < 100; i++)
        gCurrentPinballGame->unkF68[gMain.unk6][i] = gMain.spriteGroups[i].available;

    DmaCopy16(3, (void *)OBJ_PLTT, gCurrentPinballGame->unk74C[gMain.unk6], OBJ_PLTT_SIZE);
    DmaCopy16(3, (void *)BG_PLTT, gCurrentPinballGame->unkB4C[gMain.unk6], BG_PLTT_SIZE);
    if (!arg0)
        return;

    gCurrentPinballGame->bgOffsets0 = gMain.bgOffsets[0];
    gCurrentPinballGame->bgOffsets1 = gMain.bgOffsets[1];
    gCurrentPinballGame->bgOffsets2 = gMain.bgOffsets[2];
    gCurrentPinballGame->bgOffsets3 = gMain.bgOffsets[3];
    gCurrentPinballGame->field = gMain.selectedField;
    gCurrentPinballGame->unk10FE = gMain.unk5;
    gCurrentPinballGame->unk10FF = gMain.unk6;
    gCurrentPinballGame->unk1101 = gMain.unkF;
    gCurrentPinballGame->unk1102 = gMain.unk10;
    gCurrentPinballGame->unk1103 = gMain.unk11;
    gCurrentPinballGame->unk1320 = gMain.unk12;
    gCurrentPinballGame->unk1322 = gMain.unk14;
    gCurrentPinballGame->unk1324 = gMain.unk28;
    gCurrentPinballGame->unk1326 = gMain.unk2A;
    gCurrentPinballGame->unk1110 = gCurrentPinballGame->unk1106;
    gCurrentPinballGame->unk1112 = gCurrentPinballGame->unk1108;
    gCurrentPinballGame->unk1114 = gCurrentPinballGame->unk110A;
    gCurrentPinballGame->unk1116 = gCurrentPinballGame->unk110C;
    gCurrentPinballGame->unk1118 = gCurrentPinballGame->unk110E;
    gCurrentPinballGame->ballSpeed = gMain_saveData.ballSpeed;

    for (i = 0; i < NUM_EREADER_CARDS; i++)
        gCurrentPinballGame->eReaderBonuses[i] = gMain.eReaderBonuses[i];
}

void sub_4B654(void)
{
    gCurrentPinballGame->unk0 = 1;
    WriteAndVerifySramFast((const u8 *)gCurrentPinballGame, (void *)SRAM + 0x544, sizeof(*gCurrentPinballGame));
}
