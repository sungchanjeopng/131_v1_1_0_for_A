# C1D-330 BLE 변경사항

## 2026-04-01 | BLE 페어링 버그 수정

### 1. BLE RX 버퍼 오버플로우 수정
- **파일**: `_Wess/function/data/data_commu.c`
- **증상**: 페어링(BLE 연결) 성공 후 `+DISCONNECTED`만 표시됨
- **원인**: `bt_rx_buf[20]` 크기가 BLE 모듈(BoT-nLE521)의 ASCII 메시지를 담기에 부족
  - `+CONNECTED[xx:xx:xx:xx:xx:xx]\r\n` ≈ 31바이트 → 20바이트 버퍼 오버플로우
  - 오버플로우 방지 코드(`bt_rx_cnt >= sizeof(bt_rx_buf)`)에 의해 수신 중 리셋
  - `strstr("+CONNECTED")` 매칭 실패 → `gBle_connected = 1` 설정 안 됨
  - `+DISCONNECTED\r\n` (16바이트)는 정상 수신되어 해제만 인식
- **수정**: `bt_rx_buf[20]` → `bt_rx_buf[64]`

### 2. DaBT_SendDeviceInfo() 활성화 (이전 반영)
- **파일**: `_Wess/function/data/data_commu.c`
- **내용**: Pairing cmd `0xF0` 수신 시 `DaBT_SendDeviceInfo()` 호출 주석 해제
- **수정**: `lMnSys` 직접 접근 → getter 함수(`MnSYS_PrGet_site_name_hi/lo`) 사용
- **수정**: fwVersion extern 하드코딩 → `_APP_VERISON` 문자열 파싱으로 변경
