// Copyright (C) 2023 Algoltek, Inc.
// SPDX-License-Identifier: LGPL-2.1+

#[derive(Getters,ValidateBytes)]
struct AlgoltekProductIdentity {
    header_len: u8,
    header: u64le == 0x4B45544C4F474C41, // 'A' 'L' 'G' 'O' 'L' 'T' 'E' 'K'
    product_name_len: u8,
    product_name: [char; 16],
    version_len: u8,
    version: [char; 48],
}

enum AlgoltekCmd {
    RDR = 0x06,
    WRR,
    RDV,
    EN,
    WRF = 0x10,
    ISP = 0x13,
    ERS = 0x19,
    BOT = 0x1D,
    RST = 0x20,
}