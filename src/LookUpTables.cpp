#include "LookUpTables.hpp"

    const U64 LookUpTables::MASK_RANK[]={0xFF,
                                0xFF00,
                                0xFF0000,
                                0xFF000000,
                                0xFF00000000,
                                0xFF0000000000,
                                0xFF000000000000,
                                0xFF00000000000000
                                };

    const U64 LookUpTables::MASK_FILE[]={0x0101010101010101,
                                0x202020202020202,
                                0x404040404040404,
                                0x808080808080808,
                                0x1010101010101010,
                                0x2020202020202020,
                                0x4040404040404040,
                                0x8080808080808080
                                };

    const U64 LookUpTables::CLEAR_RANK[]={0xFFFFFFFFFFFFFF00,
                                0xFFFFFFFFFFFF00FF,
                                0xFFFFFFFFFF00FFFF,
                                0xFFFFFFFF00FFFFFF,
                                0xFFFFFF00FFFFFFFF,
                                0xFFFF00FFFFFFFFFF,
                                0xFF00FFFFFFFFFFFF,
                                0x00FFFFFFFFFFFFFF
                                };

    const U64 LookUpTables::CLEAR_FILE[]={0xFEFEFEFEFEFEFEFE,
                                0xFDFDFDFDFDFDFDFD,
                                0xFBFBFBFBFBFBFBFB,
                                0xF7F7F7F7F7F7F7F7,
                                0xEFEFEFEFEFEFEFEF,
                                0xDFDFDFDFDFDFDFDF,
                                0xBFBFBFBFBFBFBFBF,
                                0x7F7F7F7F7F7F7F7F
                                };


    const U64 LookUpTables::ROOK_INITIAL_POS = {8100000000000081};

