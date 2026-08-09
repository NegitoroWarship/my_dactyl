# Sakoa Dactyl — BMP Boost / ZMK

Hand-wired wireless split keyboard using two BMP Boost controllers.

## 現在のキーマップ

キーボードを表向きにして、使用者側から見た配置です。キーキャップに印字されて
いる文字ではなく、PCへ実際に送信されるキー／操作を示します。

### ベースレイヤー

```text
LEFT HAND                                      RIGHT HAND

[ 1 ][ 2 ][ 3 ][ 4 ][ 5 ][ 6 ]       [ 7 ][ 8 ][ 9 ][ 0 ][ - ][ = ][ \ ]
[Tab][ Q ][ W ][ E ][ R ][ T ]       [ Y ][ U ][ I ][ O ][ P ][ [ ][ ] ]
[Ctrl][ A ][ S ][ D ][ F ][ G ]      [ H ][ J ][ K ][ L ][ ; ][ ' ][Enter]
[Shift][ Z ][ X ][ C ][ V ][ B ]     [ N ][ M ][ , ][ . ][ / ][ Up][Shift]

                    [Win][Alt][Space] [Bksp][Del][Fn][ ` ][Left][Down][Right]
                                                                    [Esc]
                                                     (bottom protruding key)
```

- `Fn` は押している間だけ有効になるレイヤーキーです。
- 右手の `Esc` は、右下に1個だけ飛び出しているキーです。
- `\` は Shift と同時に押すと `|` になります（PC側のキーボード配列設定に
  よって変わる場合があります）。

### Functionレイヤー（`Fn` を押している間）

下図に書かれたキーだけが変化します。`--` の位置は透過で、ベースレイヤーと
同じキーとして動作します。

```text
LEFT HAND                                      RIGHT HAND

[F1 ][F2 ][F3 ][F4 ][F5 ][F6 ]       [F7 ][F8 ][F9 ][F10][F11][F12][ -- ]
[ --][BT1][BT2][BT3][BT4][BT5]       [ --][ --][ --][ --][ --][ --][ --]
[ --][ --][ --][ --][ --][ --]      [ --][ --][ --][ --][ --][ --][ --]
[ --][ --][ --][ --][ --][CLR]      [ --][ --][ --][ --][ --][ --][ --]

                    [ --][ --][ --]  [ --][ --][Fn ][ --][ --][ --][ --]
                                                                  [PrtSc]
```

| キー操作 | 結果 |
| --- | --- |
| `Fn+1` ... `Fn+0` | `F1` ... `F10` |
| `Fn+-` / `Fn+=` | `F11` / `F12` |
| `Fn+Esc` | Print Screen |
| `Fn+Q` / `Fn+W` / `Fn+E` / `Fn+R` / `Fn+T` | Bluetooth接続先1 / 2 / 3 / 4 / 5を選択 |
| `Fn+B` | 現在選択中のBluetooth接続先について、保存されたペアリング情報を削除 |

### キーキャップの印字と実際の動作が異なるキー

| 側 | キーキャップの印字 | 実際の動作 |
| --- | --- | --- |
| 左手 | `Caps Lock` | 左Ctrl |
| 左手 | `Meta` | Windows/GUI |
| 左手 | `Super` | Space |
| 右手 | `Scroll` | `\`（Shiftと同時に押すと `\|`） |
| 右手 | `Cmd` | 右Shift |
| 右手 | `Func` | 押している間Functionレイヤーを有効化 |

ファームウェア上の定義は
[`boards/shields/sakoa_dactyl/sakoa_dactyl.keymap`](boards/shields/sakoa_dactyl/sakoa_dactyl.keymap)
を参照してください。

## Build targets

- Board: `bmp_boost` (the module Kconfig marks the official BMP Boost board as ZMK-compatible)
- `sakoa_dactyl_left`: central, 5 rows x 6 columns
- `sakoa_dactyl_right`: peripheral, 6 rows x 7 columns
- `settings_reset`: clears saved BLE/settings before the first paired flash

## Electrical pin order

| Side | Columns | Rows |
| --- | --- | --- |
| Left | `5/A3, 0, 30/A6, 3/A1, 46, 47` | `19, 20, 22, 23, 32` |
| Right | `5/A3, 0, 30/A6, 3/A1, 46, 47, 10` | `19, 20, 22, 23, 32, 35` |

Diode direction is `col2row`.

## Matrix-coordinate assumptions from the supplied photos

- Left main keys: `R0-R3 / C0-C5`.
- Left thumb keys: `R4/C3 = Win`, `R4/C4 = Alt`, `R4/C5 = Space`.
- Right main keys: `R0-R3 / C0-C6`.
- Right thumb row: `R4/C0-C6 = Backspace, Delete, Func, Grave, Left, Down, Right`.
- Right single-key row: `R5/C0 = Esc`.
- `Func` is momentary layer 1.
- `Func+1` through `Func+0` produce `F1` through `F10`.
- `Func+-` produces `F11`, `Func+=` produces `F12`, and `Func+Esc` produces
  `Print Screen`.
- `Func+Backslash` remains unchanged/transparent.

If a thumb key is electrically connected to a different column, update only the
`map` in `boards/shields/sakoa_dactyl/sakoa_dactyl.dtsi` after a continuity test.
