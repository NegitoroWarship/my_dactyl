# Sakoa Dactyl — BMP Boost / ZMK

Hand-wired wireless split keyboard using two BMP Boost controllers.

## Build targets

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
