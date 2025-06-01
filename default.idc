//
// Xbox360 Basefile Info - Created by XexTool
//

#include <idc.idc>
#include <x360_imports.idc>


static MakeNameForce(addr, name)
{
    auto num, name_fixed;
    if( MakeNameEx(addr, name, SN_NOWARN) )
        return;
    for(num=0; num<999; num++)
    {
        name_fixed = form("%s_%d", name, num);
        if( MakeNameEx(addr, name_fixed, SN_NOWARN) )
            return;
    }
}

static GetSectionAddr(sectName)
{
	auto seg_addr, seg_base;
	seg_base = SegByName(sectName);
	return SegByBase(seg_base);
}

static SetupSection(startAddr, endAddr, segClass, perms, name, base)
{
    SetSelector(base, 0);
    SegCreate(startAddr, endAddr, base, 1, 3, 2);
    SegClass(startAddr, segClass);
    SegRename(startAddr, name);
    SetSegmentAttr(startAddr, SEGATTR_PERM, perms); // 4=read, 2=write, 1=execute
    SetSegmentAttr(startAddr, SEGATTR_FLAGS, 0x10); // SFL_LOADER
    SegDefReg(startAddr, "%r26", 0);
    SegDefReg(startAddr, "%r27", 0);
    SegDefReg(startAddr, "%r28", 0);
    SegDefReg(startAddr, "%r29", 0);
    SegDefReg(startAddr, "%r30", 0);
    SegDefReg(startAddr, "%r31", 0);
}

static SetupSections()
{
    auto addr;

    SetupSection(0x82000600, 0x8221F52C, "DATA", 4, ".rdata", 1);
    SetupSection(0x8221F600, 0x82281D98, "DATA", 4, ".pdata", 2);
    SetupSection(0x82290000, 0x830DAA6C, "CODE", 5, ".text", 3);
    SetupSection(0x830DAC00, 0x830F2AB4, "CODE", 5, ".embsec_", 4);
    SetupSection(0x830F2C00, 0x83109428, "CODE", 5, ".embsec_", 5);
    SetupSection(0x83109600, 0x8310B45C, "CODE", 5, ".embsec_", 6);
    SetupSection(0x8310B600, 0x8311257C, "CODE", 5, ".embsec_", 7);
    SetupSection(0x83112600, 0x83128C54, "CODE", 5, ".embsec_", 8);
    SetupSection(0x83128E00, 0x8312A100, "CODE", 5, ".embsec_", 9);
    SetupSection(0x8312A200, 0x8312A4D4, "CODE", 5, ".embsec_", 10);
    SetupSection(0x8312A600, 0x8312D330, "CODE", 5, ".embsec_", 11);
    SetupSection(0x83130000, 0x83378E98, "DATA", 6, ".data", 12);
    SetupSection(0x83379000, 0x83379009, "DATA", 6, ".tls", 13);
    SetupSection(0x83379200, 0x8337920C, "DATA", 6, ".XBMOVIE", 14);

    // remove unused "leftovers" of the original binary segment
    while( (addr = SegByBase(0)) != BADADDR )
        DelSeg(addr, SEGMOD_KILL|SEGMOD_SILENT);
}

static SetupResources()
{
    SetupSection(0x83380000, 0x833BC683, "DATA", 4, "4D5307FA", 15);
}

static RemoveEmptySections()
{
    auto seg_addr, seg_num;
    for(seg_num=0; seg_num<500; seg_num=seg_num+1)
    {
        seg_addr = GetSectionAddr(form( "seg%03d", seg_num) );
        if(seg_addr != -1)
            SegDelete(seg_addr, 1);
    }
}


static SetupImportFunc(importAddr, funcAddr, importNum, name)
{
    auto func_name;
    func_name = DoNameGen(name, 0, importNum);

    MakeNameForce(importAddr, "__imp__" + func_name);
    MakeDword(importAddr);

    PatchWord(funcAddr, 0x3860);
    PatchWord(funcAddr + 4, 0x3880);
    MakeUnknown(funcAddr, 0x10, 0); // DOUNK_SIMPLE
    MakeCode(funcAddr);
    MakeNameForce(funcAddr, func_name);
    MakeFunction(funcAddr, funcAddr + 0x10);
    SetFunctionFlags(funcAddr, FUNC_LIB);
}

static SetupImportData(importAddr, importNum, name)
{
    auto data_name;
    data_name = DoNameGen(name, 0, importNum);

    MakeNameForce(importAddr, data_name);
    MakeDword(importAddr);
}

static setupImports_0_xam_xex_0()
{
    SetupImportFunc(0x82000600, 0x830D9E2C, 0x1A8, "xam.xex");
    SetupImportFunc(0x82000604, 0x830D9E3C, 0x1A7, "xam.xex");
    SetupImportFunc(0x82000608, 0x830D9E4C, 0x190, "xam.xex");
    SetupImportFunc(0x8200060C, 0x830D9C8C, 0x191, "xam.xex");
    SetupImportFunc(0x82000610, 0x830D9CCC, 0x192, "xam.xex");
    SetupImportFunc(0x82000614, 0x830D9E5C, 0x2DC, "xam.xex");
    SetupImportFunc(0x82000618, 0x830D9E6C, 0x3CD, "xam.xex");
    SetupImportFunc(0x8200061C, 0x830D9E7C, 0x3CB, "xam.xex");
    SetupImportFunc(0x82000620, 0x830D9E8C, 0x1A9, "xam.xex");
    SetupImportFunc(0x82000624, 0x830DAA4C, 0x219, "xam.xex");
    SetupImportFunc(0x82000628, 0x830DA95C, 0x280, "xam.xex");
    SetupImportFunc(0x8200062C, 0x830DA94C, 0x250, "xam.xex");
    SetupImportFunc(0x82000630, 0x830DA93C, 0x1F8, "xam.xex");
    SetupImportFunc(0x82000634, 0x830DA92C, 0x28A, "xam.xex");
    SetupImportFunc(0x82000638, 0x830DA91C, 0x20A, "xam.xex");
    SetupImportFunc(0x8200063C, 0x830DA90C, 0x2EE, "xam.xex");
    SetupImportFunc(0x82000640, 0x830DA8FC, 0x210, "xam.xex");
    SetupImportFunc(0x82000644, 0x830DA8EC, 0x28B, "xam.xex");
    SetupImportFunc(0x82000648, 0x830DA8DC, 0x28C, "xam.xex");
    SetupImportFunc(0x8200064C, 0x830DA8CC, 0x1F4, "xam.xex");
    SetupImportFunc(0x82000650, 0x830DA8BC, 0x1FC, "xam.xex");
    SetupImportFunc(0x82000654, 0x830DA8AC, 0x01D, "xam.xex");
    SetupImportFunc(0x82000658, 0x830DA89C, 0x01B, "xam.xex");
    SetupImportFunc(0x8200065C, 0x830DA88C, 0x01A, "xam.xex");
    SetupImportFunc(0x82000660, 0x830DA87C, 0x018, "xam.xex");
    SetupImportFunc(0x82000664, 0x830DA86C, 0x016, "xam.xex");
    SetupImportFunc(0x82000668, 0x830DA85C, 0x014, "xam.xex");
    SetupImportFunc(0x8200066C, 0x830DA84C, 0x012, "xam.xex");
    SetupImportFunc(0x82000670, 0x830DA83C, 0x00C, "xam.xex");
    SetupImportFunc(0x82000674, 0x830DA82C, 0x00B, "xam.xex");
    SetupImportFunc(0x82000678, 0x830DA81C, 0x009, "xam.xex");
    SetupImportFunc(0x8200067C, 0x830DA80C, 0x008, "xam.xex");
    SetupImportFunc(0x82000680, 0x830DA7FC, 0x007, "xam.xex");
    SetupImportFunc(0x82000684, 0x830DA7EC, 0x006, "xam.xex");
    SetupImportFunc(0x82000688, 0x830DA7DC, 0x004, "xam.xex");
    SetupImportFunc(0x8200068C, 0x830DA7CC, 0x003, "xam.xex");
    SetupImportFunc(0x82000690, 0x830DA7BC, 0x002, "xam.xex");
    SetupImportFunc(0x82000694, 0x830DA7AC, 0x001, "xam.xex");
    SetupImportFunc(0x82000698, 0x830DA0DC, 0x1A6, "xam.xex");
    SetupImportFunc(0x8200069C, 0x830DA0EC, 0x3D1, "xam.xex");
    SetupImportFunc(0x820006A0, 0x830DA0FC, 0xA28, "xam.xex");
    SetupImportFunc(0x820006A4, 0x830DA10C, 0xA2A, "xam.xex");
    SetupImportFunc(0x820006A8, 0x830DA11C, 0x1A0, "xam.xex");
    SetupImportFunc(0x820006AC, 0x830DA12C, 0x1A1, "xam.xex");
    SetupImportFunc(0x820006B0, 0x830DA13C, 0x2BC, "xam.xex");
    SetupImportFunc(0x820006B4, 0x830DA14C, 0x2CB, "xam.xex");
    SetupImportFunc(0x820006B8, 0x830DA15C, 0x2CA, "xam.xex");
    SetupImportFunc(0x820006BC, 0x830DA16C, 0x2D9, "xam.xex");
    SetupImportFunc(0x820006C0, 0x830DA17C, 0x1A4, "xam.xex");
    SetupImportFunc(0x820006C4, 0x830DA18C, 0x259, "xam.xex");
    SetupImportFunc(0x820006C8, 0x830DA19C, 0x25A, "xam.xex");
    SetupImportFunc(0x820006CC, 0x830DA1AC, 0x267, "xam.xex");
    SetupImportFunc(0x820006D0, 0x830DA1BC, 0x260, "xam.xex");
    SetupImportFunc(0x820006D4, 0x830DA1CC, 0x262, "xam.xex");
    SetupImportFunc(0x820006D8, 0x830DA1DC, 0x25C, "xam.xex");
    SetupImportFunc(0x820006DC, 0x830DA1EC, 0x25E, "xam.xex");
    SetupImportFunc(0x820006E0, 0x830DA1FC, 0x1F7, "xam.xex");
    SetupImportFunc(0x820006E4, 0x830DA20C, 0x1B3, "xam.xex");
    SetupImportFunc(0x820006E8, 0x830DA21C, 0x1B1, "xam.xex");
    SetupImportFunc(0x820006EC, 0x830DA22C, 0x1AF, "xam.xex");
    SetupImportFunc(0x820006F0, 0x830DA23C, 0x3CC, "xam.xex");
    SetupImportFunc(0x820006F4, 0x830DA79C, 0x049, "xam.xex");
    SetupImportFunc(0x820006F8, 0x830DA78C, 0x044, "xam.xex");
    SetupImportFunc(0x820006FC, 0x830DA77C, 0x043, "xam.xex");
    SetupImportFunc(0x82000700, 0x830DA76C, 0x034, "xam.xex");
    SetupImportFunc(0x82000704, 0x830DA75C, 0x282, "xam.xex");
    SetupImportFunc(0x82000708, 0x830DA74C, 0x033, "xam.xex");
    SetupImportFunc(0x8200070C, 0x830DAA5C, 0x21A, "xam.xex");
}

static setupImports_1_xboxkrnl_exe_0()
{
    SetupImportFunc(0x82000720, 0x830DA34C, 0x25A, "xboxkrnl.exe");
    SetupImportFunc(0x82000724, 0x830DA35C, 0x259, "xboxkrnl.exe");
    SetupImportFunc(0x82000728, 0x830DA36C, 0x257, "xboxkrnl.exe");
    SetupImportFunc(0x8200072C, 0x830DA37C, 0x192, "xboxkrnl.exe");
    SetupImportFunc(0x82000730, 0x830DA38C, 0x256, "xboxkrnl.exe");
    SetupImportFunc(0x82000734, 0x830DA39C, 0x0DB, "xboxkrnl.exe");
    SetupImportFunc(0x82000738, 0x830DA3AC, 0x03B, "xboxkrnl.exe");
    SetupImportFunc(0x8200073C, 0x830DA3BC, 0x103, "xboxkrnl.exe");
    SetupImportFunc(0x82000740, 0x830DA3CC, 0x104, "xboxkrnl.exe");
    SetupImportFunc(0x82000744, 0x830DA3DC, 0x07D, "xboxkrnl.exe");
    SetupImportFunc(0x82000748, 0x830DA3EC, 0x08F, "xboxkrnl.exe");
    SetupImportFunc(0x8200074C, 0x830DA3FC, 0x0B0, "xboxkrnl.exe");
    SetupImportFunc(0x82000750, 0x830DA40C, 0x09D, "xboxkrnl.exe");
    SetupImportFunc(0x82000754, 0x830DA41C, 0x05F, "xboxkrnl.exe");
    SetupImportFunc(0x82000758, 0x830DA42C, 0x015, "xboxkrnl.exe");
    SetupImportFunc(0x8200075C, 0x830D9D9C, 0x084, "xboxkrnl.exe");
    SetupImportFunc(0x82000760, 0x830DA43C, 0x019, "xboxkrnl.exe");
    SetupImportFunc(0x82000764, 0x830DA44C, 0x0C6, "xboxkrnl.exe");
    SetupImportFunc(0x82000768, 0x830DA45C, 0x197, "xboxkrnl.exe");
    SetupImportFunc(0x8200076C, 0x830DA46C, 0x196, "xboxkrnl.exe");
    SetupImportFunc(0x82000770, 0x830DA47C, 0x195, "xboxkrnl.exe");
    SetupImportFunc(0x82000774, 0x830D9E0C, 0x127, "xboxkrnl.exe");
    SetupImportFunc(0x82000778, 0x830D9DEC, 0x142, "xboxkrnl.exe");
    SetupImportFunc(0x8200077C, 0x830D9DDC, 0x12D, "xboxkrnl.exe");
    SetupImportFunc(0x82000780, 0x830DA49C, 0x00D, "xboxkrnl.exe");
    SetupImportFunc(0x82000784, 0x830DA4AC, 0x041, "xboxkrnl.exe");
    SetupImportFunc(0x82000788, 0x830DA4BC, 0x10F, "xboxkrnl.exe");
    SetupImportFunc(0x8200078C, 0x830DA4CC, 0x037, "xboxkrnl.exe");
    SetupImportFunc(0x82000790, 0x830DA4DC, 0x039, "xboxkrnl.exe");
    SetupImportFunc(0x82000794, 0x830DA4EC, 0x00B, "xboxkrnl.exe");
    SetupImportFunc(0x82000798, 0x830DA4FC, 0x11D, "xboxkrnl.exe");
    SetupImportFunc(0x8200079C, 0x830DA50C, 0x035, "xboxkrnl.exe");
    SetupImportFunc(0x820007A0, 0x830DA51C, 0x0B4, "xboxkrnl.exe");
    SetupImportFunc(0x820007A4, 0x830DA52C, 0x0B1, "xboxkrnl.exe");
    SetupImportFunc(0x820007A8, 0x830DA53C, 0x149, "xboxkrnl.exe");
    SetupImportFunc(0x820007AC, 0x830DA54C, 0x109, "xboxkrnl.exe");
    SetupImportFunc(0x820007B0, 0x830DA55C, 0x034, "xboxkrnl.exe");
    SetupImportFunc(0x820007B4, 0x830DA56C, 0x047, "xboxkrnl.exe");
    SetupImportFunc(0x820007B8, 0x830DA57C, 0x045, "xboxkrnl.exe");
    SetupImportFunc(0x820007BC, 0x830DA58C, 0x03C, "xboxkrnl.exe");
    SetupImportFunc(0x820007C0, 0x830DA59C, 0x0D9, "xboxkrnl.exe");
    SetupImportData(0x820007C4,             0x1BE, "xboxkrnl.exe");
    SetupImportFunc(0x820007C8, 0x830DA5AC, 0x25B, "xboxkrnl.exe");
    SetupImportFunc(0x820007CC, 0x830DA5BC, 0x1C7, "xboxkrnl.exe");
    SetupImportFunc(0x820007D0, 0x830DA5CC, 0x1BD, "xboxkrnl.exe");
    SetupImportData(0x820007D4,             0x266, "xboxkrnl.exe");
    SetupImportFunc(0x820007D8, 0x830D9D6C, 0x089, "xboxkrnl.exe");
    SetupImportFunc(0x820007DC, 0x830DA5DC, 0x1B6, "xboxkrnl.exe");
    SetupImportFunc(0x820007E0, 0x830DA5EC, 0x1C3, "xboxkrnl.exe");
    SetupImportFunc(0x820007E4, 0x830DA5FC, 0x1DF, "xboxkrnl.exe");
    SetupImportFunc(0x820007E8, 0x830DA60C, 0x0BE, "xboxkrnl.exe");
    SetupImportFunc(0x820007EC, 0x830DA61C, 0x1D9, "xboxkrnl.exe");
    SetupImportFunc(0x820007F0, 0x830DA62C, 0x1B4, "xboxkrnl.exe");
    SetupImportFunc(0x820007F4, 0x830DA63C, 0x13B, "xboxkrnl.exe");
    SetupImportFunc(0x820007F8, 0x830DA64C, 0x1B9, "xboxkrnl.exe");
    SetupImportFunc(0x820007FC, 0x830DA65C, 0x1DC, "xboxkrnl.exe");
    SetupImportFunc(0x82000800, 0x830DA66C, 0x1D5, "xboxkrnl.exe");
    SetupImportFunc(0x82000804, 0x830DA67C, 0x1D3, "xboxkrnl.exe");
    SetupImportFunc(0x82000808, 0x830DA68C, 0x1C6, "xboxkrnl.exe");
    SetupImportFunc(0x8200080C, 0x830DA69C, 0x1CA, "xboxkrnl.exe");
    SetupImportFunc(0x82000810, 0x830DA6AC, 0x1BA, "xboxkrnl.exe");
    SetupImportFunc(0x82000814, 0x830DA6BC, 0x1C9, "xboxkrnl.exe");
    SetupImportFunc(0x82000818, 0x830DA6CC, 0x1C2, "xboxkrnl.exe");
    SetupImportFunc(0x8200081C, 0x830DA6DC, 0x1C5, "xboxkrnl.exe");
    SetupImportFunc(0x82000820, 0x830DA6EC, 0x1B1, "xboxkrnl.exe");
    SetupImportData(0x82000824,             0x1C0, "xboxkrnl.exe");
    SetupImportFunc(0x82000828, 0x830DA6FC, 0x14D, "xboxkrnl.exe");
    SetupImportFunc(0x8200082C, 0x830DA70C, 0x26A, "xboxkrnl.exe");
    SetupImportData(0x82000830,             0x1C1, "xboxkrnl.exe");
    SetupImportFunc(0x82000834, 0x830DA71C, 0x269, "xboxkrnl.exe");
    SetupImportFunc(0x82000838, 0x830DA72C, 0x06C, "xboxkrnl.exe");
    SetupImportFunc(0x8200083C, 0x830DA73C, 0x06B, "xboxkrnl.exe");
    SetupImportFunc(0x82000840, 0x830DA32C, 0x0E2, "xboxkrnl.exe");
    SetupImportFunc(0x82000844, 0x830D9DBC, 0x140, "xboxkrnl.exe");
    SetupImportFunc(0x82000848, 0x830DA31C, 0x13F, "xboxkrnl.exe");
    SetupImportFunc(0x8200084C, 0x830DA30C, 0x0F5, "xboxkrnl.exe");
    SetupImportFunc(0x82000850, 0x830D9E1C, 0x083, "xboxkrnl.exe");
    SetupImportFunc(0x82000854, 0x830DA2FC, 0x009, "xboxkrnl.exe");
    SetupImportFunc(0x82000858, 0x830DA2EC, 0x00F, "xboxkrnl.exe");
    SetupImportFunc(0x8200085C, 0x830DA2DC, 0x0FF, "xboxkrnl.exe");
    SetupImportFunc(0x82000860, 0x830DA2CC, 0x0E7, "xboxkrnl.exe");
    SetupImportFunc(0x82000864, 0x830DA2BC, 0x021, "xboxkrnl.exe");
    SetupImportFunc(0x82000868, 0x830D9DFC, 0x12C, "xboxkrnl.exe");
    SetupImportFunc(0x8200086C, 0x830D9CEC, 0x151, "xboxkrnl.exe");
    SetupImportFunc(0x82000870, 0x830D9D0C, 0x0F6, "xboxkrnl.exe");
    SetupImportFunc(0x82000874, 0x830D9D2C, 0x0CE, "xboxkrnl.exe");
    SetupImportFunc(0x82000878, 0x830DA2AC, 0x0D4, "xboxkrnl.exe");
    SetupImportFunc(0x8200087C, 0x830D9D8C, 0x0F2, "xboxkrnl.exe");
    SetupImportData(0x82000880,             0x0AD, "xboxkrnl.exe");
    SetupImportData(0x82000884,             0x00E, "xboxkrnl.exe");
    SetupImportFunc(0x82000888, 0x830DA29C, 0x05D, "xboxkrnl.exe");
    SetupImportFunc(0x8200088C, 0x830DA28C, 0x147, "xboxkrnl.exe");
    SetupImportFunc(0x82000890, 0x830DA27C, 0x119, "xboxkrnl.exe");
    SetupImportFunc(0x82000894, 0x830DA26C, 0x153, "xboxkrnl.exe");
    SetupImportFunc(0x82000898, 0x830D9CAC, 0x155, "xboxkrnl.exe");
    SetupImportFunc(0x8200089C, 0x830D9C9C, 0x154, "xboxkrnl.exe");
    SetupImportFunc(0x820008A0, 0x830DA25C, 0x152, "xboxkrnl.exe");
    SetupImportFunc(0x820008A4, 0x830DA24C, 0x052, "xboxkrnl.exe");
    SetupImportFunc(0x820008A8, 0x830DA33C, 0x0FE, "xboxkrnl.exe");
    SetupImportFunc(0x820008AC, 0x830D9D5C, 0x04D, "xboxkrnl.exe");
    SetupImportFunc(0x820008B0, 0x830D9CFC, 0x0FD, "xboxkrnl.exe");
    SetupImportFunc(0x820008B4, 0x830DA0AC, 0x136, "xboxkrnl.exe");
    SetupImportFunc(0x820008B8, 0x830DA09C, 0x0EE, "xboxkrnl.exe");
    SetupImportFunc(0x820008BC, 0x830DA08C, 0x11B, "xboxkrnl.exe");
    SetupImportFunc(0x820008C0, 0x830DA07C, 0x066, "xboxkrnl.exe");
    SetupImportFunc(0x820008C4, 0x830DA06C, 0x053, "xboxkrnl.exe");
    SetupImportFunc(0x820008C8, 0x830DA05C, 0x126, "xboxkrnl.exe");
    SetupImportFunc(0x820008CC, 0x830DA04C, 0x0D2, "xboxkrnl.exe");
    SetupImportFunc(0x820008D0, 0x830DA03C, 0x0F0, "xboxkrnl.exe");
    SetupImportFunc(0x820008D4, 0x830DA02C, 0x0F1, "xboxkrnl.exe");
    SetupImportFunc(0x820008D8, 0x830DA01C, 0x0E4, "xboxkrnl.exe");
    SetupImportFunc(0x820008DC, 0x830DA00C, 0x0EF, "xboxkrnl.exe");
    SetupImportFunc(0x820008E0, 0x830D9FFC, 0x0E8, "xboxkrnl.exe");
    SetupImportFunc(0x820008E4, 0x830D9FEC, 0x028, "xboxkrnl.exe");
    SetupImportData(0x820008E8,             0x193, "xboxkrnl.exe");
    SetupImportFunc(0x820008EC, 0x830D9FDC, 0x12B, "xboxkrnl.exe");
    SetupImportData(0x820008F0,             0x059, "xboxkrnl.exe");
    SetupImportFunc(0x820008F4, 0x830D9FCC, 0x097, "xboxkrnl.exe");
    SetupImportFunc(0x820008F8, 0x830D9FBC, 0x0FC, "xboxkrnl.exe");
    SetupImportData(0x820008FC,             0x01B, "xboxkrnl.exe");
    SetupImportFunc(0x82000900, 0x830D9FAC, 0x110, "xboxkrnl.exe");
    SetupImportFunc(0x82000904, 0x830D9F9C, 0x099, "xboxkrnl.exe");
    SetupImportFunc(0x82000908, 0x830D9F8C, 0x105, "xboxkrnl.exe");
    SetupImportFunc(0x8200090C, 0x830D9F7C, 0x05A, "xboxkrnl.exe");
    SetupImportFunc(0x82000910, 0x830D9DCC, 0x143, "xboxkrnl.exe");
    SetupImportFunc(0x82000914, 0x830D9F6C, 0x0F7, "xboxkrnl.exe");
    SetupImportFunc(0x82000918, 0x830D9F5C, 0x0DF, "xboxkrnl.exe");
    SetupImportFunc(0x8200091C, 0x830D9F4C, 0x1A5, "xboxkrnl.exe");
    SetupImportFunc(0x82000920, 0x830D9F3C, 0x003, "xboxkrnl.exe");
    SetupImportFunc(0x82000924, 0x830D9F2C, 0x194, "xboxkrnl.exe");
    SetupImportFunc(0x82000928, 0x830D9DAC, 0x010, "xboxkrnl.exe");
    SetupImportFunc(0x8200092C, 0x830D9F1C, 0x0D1, "xboxkrnl.exe");
    SetupImportData(0x82000930,             0x0CF, "xboxkrnl.exe");
}

static setupImports_1_xboxkrnl_exe_1()
{
    SetupImportData(0x830D9F0C,             0x0CF, "xboxkrnl.exe");
    SetupImportData(0x82000934,             0x1AE, "xboxkrnl.exe");
    SetupImportData(0x82000938,             0x158, "xboxkrnl.exe");
    SetupImportFunc(0x8200093C, 0x830D9CDC, 0x133, "xboxkrnl.exe");
    SetupImportFunc(0x82000940, 0x830D9EFC, 0x135, "xboxkrnl.exe");
    SetupImportFunc(0x82000944, 0x830D9D3C, 0x0DC, "xboxkrnl.exe");
    SetupImportFunc(0x82000948, 0x830D9EEC, 0x0C4, "xboxkrnl.exe");
    SetupImportFunc(0x8200094C, 0x830D9EDC, 0x0BD, "xboxkrnl.exe");
    SetupImportFunc(0x82000950, 0x830D9ECC, 0x0C7, "xboxkrnl.exe");
    SetupImportFunc(0x82000954, 0x830D9EBC, 0x0BA, "xboxkrnl.exe");
    SetupImportFunc(0x82000958, 0x830D9D1C, 0x0CC, "xboxkrnl.exe");
    SetupImportFunc(0x8200095C, 0x830D9EAC, 0x0DA, "xboxkrnl.exe");
    SetupImportFunc(0x82000960, 0x830D9CBC, 0x141, "xboxkrnl.exe");
    SetupImportFunc(0x82000964, 0x830D9E9C, 0x12E, "xboxkrnl.exe");
    SetupImportFunc(0x82000968, 0x830D9C7C, 0x130, "xboxkrnl.exe");
    SetupImportFunc(0x8200096C, 0x830D9D4C, 0x085, "xboxkrnl.exe");
    SetupImportFunc(0x82000970, 0x830D9D7C, 0x0B3, "xboxkrnl.exe");
    SetupImportFunc(0x82000974, 0x830DA96C, 0x0AE, "xboxkrnl.exe");
    SetupImportFunc(0x82000978, 0x830DA97C, 0x0AF, "xboxkrnl.exe");
    SetupImportFunc(0x8200097C, 0x830DA98C, 0x088, "xboxkrnl.exe");
    SetupImportFunc(0x82000980, 0x830DA99C, 0x1F8, "xboxkrnl.exe");
    SetupImportFunc(0x82000984, 0x830DA9AC, 0x1F7, "xboxkrnl.exe");
    SetupImportFunc(0x82000988, 0x830DA9BC, 0x092, "xboxkrnl.exe");
    SetupImportFunc(0x8200098C, 0x830DA9CC, 0x074, "xboxkrnl.exe");
    SetupImportFunc(0x82000990, 0x830DA9DC, 0x224, "xboxkrnl.exe");
    SetupImportFunc(0x82000994, 0x830DA9EC, 0x226, "xboxkrnl.exe");
    SetupImportFunc(0x82000998, 0x830DA9FC, 0x1F3, "xboxkrnl.exe");
    SetupImportFunc(0x8200099C, 0x830DAA0C, 0x1F4, "xboxkrnl.exe");
    SetupImportFunc(0x820009A0, 0x830DAA1C, 0x1F5, "xboxkrnl.exe");
    SetupImportFunc(0x820009A4, 0x830DAA2C, 0x02B, "xboxkrnl.exe");
    SetupImportFunc(0x820009A8, 0x830DAA3C, 0x02C, "xboxkrnl.exe");
    SetupImportFunc(0x820009AC, 0x830D9C6C, 0x125, "xboxkrnl.exe");
    SetupImportFunc(0x820009B0, 0x830DA48C, 0x001, "xboxkrnl.exe");
}

static SetupImports()
{
    setupImports_0_xam_xex_0();
    setupImports_1_xboxkrnl_exe_0();
    setupImports_1_xboxkrnl_exe_1();
}


static SetupExportFunc(funcAddr, exportNum, funcName)
{
    MakeUnkn(funcAddr, 0);
    MakeCode(funcAddr); 
    MakeNameForce(funcAddr, funcName);
    MakeFunction(funcAddr, BADADDR);
    AddEntryPoint(exportNum, funcAddr, funcName, 1);
}

static SetupExportData(dataAddr, exportNum, name)
{
    auto data_name;
    data_name = DoNameGen(name, 0, exportNum);

    AddEntryPoint(exportNum, dataAddr, data_name, 0);
    MakeNameForce(dataAddr, data_name);
    MakeDword(dataAddr);
}

static SetupExports()
{
    auto name;
    name = GetInputFile();


    // set start entry point
    SetupExportFunc(0x827CA440, 0x827CA440, "start");
}

static SetupExportsByName()
{
}

static SetupRegSaves()
{
	auto currAddr, i;
	
	// find all saves of gp regs
	for(currAddr=0; currAddr != BADADDR; currAddr=currAddr+4)
	{
		// find "std %r14, -0x98(%sp)" followed by "std %r15, -0x90(%sp)"
		currAddr = FindBinary(currAddr, SEARCH_DOWN, "F9 C1 FF 68 F9 E1 FF 70");
		if(currAddr == BADADDR)
			break;
		for(i=14; i<=31; i++)
		{
			MakeUnknown(currAddr, 4, 0); // DOUNK_SIMPLE
			MakeCode(currAddr);
			if(i != 31)
				MakeFunction(currAddr, currAddr + 4);
			else
				MakeFunction(currAddr, currAddr + 0x0C);
			MakeNameForce(currAddr, form("__savegprlr_%d", i));
			currAddr = currAddr + 4;
		}
	}
	
	// find all loads of gp regs
	for(currAddr=0; currAddr != BADADDR; currAddr=currAddr+4)
	{
		// find "ld  %r14, var_98(%sp)" followed by "ld  %r15, var_90(%sp)"
		currAddr = FindBinary(currAddr, SEARCH_DOWN, "E9 C1 FF 68 E9 E1 FF 70");
		if(currAddr == BADADDR)
			break;
		for(i=14; i<=31; i++)
		{
			MakeUnknown(currAddr, 4, 0); // DOUNK_SIMPLE
			MakeCode(currAddr);
			if(i != 31)
				MakeFunction(currAddr, currAddr + 4);
			else
				MakeFunction(currAddr, currAddr + 0x10);
			MakeNameForce(currAddr, form("__restgprlr_%d", i));
			currAddr = currAddr + 4;
		}
	}
}

static ConvertToCode(startAddr, endAddr)
{
    auto addr;
    if(startAddr == BADADDR || endAddr == BADADDR || startAddr>endAddr)
        return;
    
    MakeUnknown(startAddr, endAddr-startAddr, 0); // DOUNK_SIMPLE
    for(addr=startAddr&0xFFFFFFFC; addr<endAddr; addr=addr+4)
    {
        MakeCode(addr);
    }
    AnalyzeArea(startAddr, endAddr);
}

static main()
{
    // ensure file was loaded in as binary
    // if it was loaded in as PE then addresses will be incorrect
    if( GetShortPrm(INF_FILETYPE) != FT_BIN )
    {
        Warning("The file must be loaded as a BINARY file to use this script.\n"
                "Close this database and create a new one, ensuring you\n"
                "select \"Binary File\" on IDAs \"Load a new file\" dialog.");
        return;
    }
    
    // ensure file was loaded in as PPC
    if( GetCharPrm(INF_PROCNAME+0) != 'P' ||
        GetCharPrm(INF_PROCNAME+1) != 'P' ||
        GetCharPrm(INF_PROCNAME+2) != 'C' ||
        GetCharPrm(INF_PROCNAME+3) != '\0' )
    {
        Warning("The file must be loaded for the PPC processor.\n"
                "Close this database and create a new one, ensuring you\n"
                "select \"PowerPC: ppc\" on IDAs \"Load a new file\" dialog.");
        return;
    }

    // set up resources
    if( 1 == AskYN(0, "Would you like to load reources as segments?") )
        SetupResources();

    // set up sections
    SetupSections();

    // remove empty sections
    RemoveEmptySections();

    // analyse code
    if( 1 == AskYN(1, "Would you like to analyse the file as code?") )
        ConvertToCode( GetSectionAddr(".text"), SegEnd(GetSectionAddr(".text")) );

    // set up imports
    SetupImports();

    // set up exports
    SetupExports();

    // set up exports by name
    SetupExportsByName();

    // setup all reg loads/stores
    SetupRegSaves();

    // done
    Message("done\n\n");
}

