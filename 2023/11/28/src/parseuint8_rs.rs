
#[no_mangle]
pub fn parse_uint8_fastswar_rs(b: &[u8]) -> Option<u8> {
  if b.len() == 0 || b.len() > 3 { return None; }
  let p = b.as_ptr() as *const u32;
  let mut digits = unsafe { p.read_unaligned() };
  digits ^= 0x30303030;
  digits <<= (4 - b.len()) * 8;
  let num = ((digits.wrapping_mul(0x640a01)) >> 24) as u8;
  let all_digits = ((digits | (digits.wrapping_add(0x06060606))) & 0xF0F0F0F0) == 0;
  (all_digits && digits.swap_bytes() <= 0x020505).then_some(num)
}

#[no_mangle]
pub fn parse_uint8_fastswar_bob_rs(b: &[u8]) -> Option<u8> {
  let p = b.as_ptr() as *const u32;
  let mut digits = unsafe { p.read_unaligned() };
  digits ^= 0x303030;
  digits <<= (b.len() ^ 3) * 8;
  let num = ((digits.wrapping_mul(0x640a01)) >> 16) as u8;
  let all_digits = ((digits | (digits.wrapping_add(0x767676))) & 0x808080) == 0;
  (all_digits && ((b.len() ^ 3) < 3) && digits.swap_bytes() <= 0x020505ff).then_some(num)
}
