
# [OpenKey](http://open-key.org)
### [Download bản mới nhất](https://github.com/tuyenvm/OpenKey/releases)
[![GitHub release](https://img.shields.io/github/v/release/tuyenvm/OpenKey.svg)](https://github.com/tuyenvm/OpenKey/releases/latest)

### Open source Vietnamese Input App for macOS - Bộ gõ tiếng Việt nguồn mở cho macOS.
Bộ gõ tiếng Việt mới cho macOS, sử dụng kỹ thuật `Backspace`. Loại bỏ lỗi gạch chân khó chịu ở bộ gõ mặc định. Hoàn toàn miễn phí và là nguồn mở, luôn cập nhật và phát triển.

### Mã nguồn của ứng dụng được mở công khai, minh bạch dưới giấy phép GPL. Điều này nghĩa là bạn hoàn toàn có thể tải mã nguồn về tự build, cải tiến theo mục đích của bạn. Nếu bạn tái phân phối bản cải tiến của bạn, thì nó cũng phải là mã nguồn mở và thông báo bản gốc là OpenKey.

### Lưu ý, khi sử dụng OpenKey, bạn nên tắt hẳn bộ gõ khác vì 2 chương trình bộ gõ sẽ xung đột nhau, dẫn đến thao tác không chính xác.

![Giao diện](https://raw.githubusercontent.com/tuyenvm/tuyenvm.github.io/master/images/openkey-main-control.png "Main UI")
![Giao diện](https://raw.githubusercontent.com/tuyenvm/tuyenvm.github.io/master/images/openkey-main-control-2.png "Main UI")
![Giao diện](https://raw.githubusercontent.com/tuyenvm/tuyenvm.github.io/master/images/openkey-main-control-3.png "Main UI")
![Menu](https://raw.githubusercontent.com/tuyenvm/tuyenvm.github.io/master/images/openkey-small-control.png "Menu bar")
![Gõ tắt](https://raw.githubusercontent.com/tuyenvm/tuyenvm.github.io/master/images/openkey-macro.png "Macro")
![Chuyển mã](https://raw.githubusercontent.com/tuyenvm/tuyenvm.github.io/master/images/openkey-convert-tool.png "ConvertTool")

## Hỗ trợ kiểu gõ
- Telex
- VNI
- Simple Telex

## Bảng mã thông dụng:
- Unicode (Unicode dựng sẵn).
- TCVN3 (ABC).
- VNI Windows.
- Unicode Compound (Unicode tổ hợp).
- Vietnamese Locale CP 1258.
- ...

## Tính năng:
- **Modern orthography** (On/Off) - Đặt dấu oà, uý thay vì òa, úy.
- **Quick Telex** (On/Off) - Gõ nhanh (cc=ch, gg=gi, kk=kh, nn=ng, qq=qu, pp=ph, tt=th).
- **Grammar check** (On/Off) - Kiểm tra ngữ pháp.
- **Spelling check** (On/Off) - Kiểm tra chính tả.
- **Restore key if invalid word** (on/off) - Phục hồi phím với từ sai.
- **Run on startup** (On/Off) - Chạy cùng macOS.
- **Gray menu bar icon** (On/Off) - Biểu tượng xám trên thanh menu phù hợp với chế độ Dark mode.
- **Switch input mode by shortcut key** - Đổi chế độ gõ bằng phím tắt tùy chọn.
- **Autocorrect fixed** (On/Off) - Sửa lỗi autocorrect trên trình duyệt như Chrome, Safari, Firefox, Microsoft Excel.
- **Underline issue fixed on macOS** (On/Off) - Sửa lỗi gạch chân trên macOS.
- **Tạm tắt kiểm tra chính tả bằng phím Ctrl** (On/Off) (Bản 1.5 về sau).
- **Tạm tắt OpenKey bằng phím Cmd/Alt** (On/Off) (Bản 2.0.1 về sau).
- **Cho phép dùng f z w j làm phụ âm đầu** (On/Off) (Bản 1.5 về sau).
- **Gõ tắt phụ âm đầu: f->ph, j->gi, w->qu** (On/Off) (Bản 1.6 về sau).
- **Gõ tắt phụ âm cuối: g->ng, h->nh, k->ch** (On/Off) (Bản 1.6 về sau).
- **Hiện biểu tượng trên thanh Dock** (On/Off) (Bản 2.0.1 về sau). Bấm vào icon trên thanh Dock sẽ mở nhanh Bảng điều khiển.
- **Macro** - Tính năng gõ tắt vô cùng tiện lợi. Gõ tắt của macOS chỉ hỗ trợ 20 ký tự, còn OpenKey không giới hạn ký tự.
- **Chuyển chế độ thông minh:** (On/Off) (Bản 1.2 về sau) - Bạn đang dùng chế độ gõ Tiếng Việt trên ứng dụng A, bạn chuyển qua ứng dụng B trước đó bạn dùng chế độ gõ Tiếng Anh, OpenKey sẽ tự động chuyển qua chế độ gõ Tiếng Anh cho bạn, khi bạn quay lại ứng dụng A, OpenKey tất nhiên sẽ chuyển lại chế độ gõ tiếng Việt, rất cơ động.
- **Viết Hoa chữ cái đầu câu** (On/Off) (Bản 1.2 về sau) - Khi gõ văn bản dài, đôi khi bạn quên ghi hoa chữ cái đầu câu khi kết thúc một câu hoặc khi xuống hàng, tính năng này sẽ tự ghi hoa chữ cái đầu câu cho bạn, thật tuyệt vời.
- **Chế độ “Gửi từng phím”:** (On/Off) (Bản 1.1 về sau) mặc định dùng kỹ thuật mới gửi dữ liệu 1 lần thay vì gửi nhiều lần cho chuỗi ký tự, nên nếu có ứng dụng nào không tương thích, hãy bật tính năng này lên, mặc định thì nên tắt vì kỹ thuật mới sẽ chạy nhanh hơn.
- **Cập nhật tự động:** (Bản 1.3 về sau) tính năng hỗ trợ cập nhật phiên bản OpenKey mới nhất mỗi khi mở OpenKey hoặc tự check trong phần mục Giới thiệu.
- **Công cụ chuyển mã:** (Bản 1.4 về sau) hỗ trợ chuyển mã qua lại văn bản, thích hợp cho việc chuyển đổi văn bản cũ viết bằng VNI, TCVN3 qua Unicode,... Hỗ trợ cấu hình phím tắt chuyển mã nhanh, bảng cấu hình tùy chọn chuyển mã.
- **Tự ghi nhớ bảng mã theo ứng dụng:** (Bản 2.0.1 về sau) Phù hợp cho các bạn dùng Photoshop, CAD,... với các bảng mã VNI, TCVN3. OpenKey tự ghi nhớ ứng dụng nào dùng bảng mã nào để lần sau sử dụng Photoshop, CAD,... OpenKey có thể tự chuyển sang bảng mã đó.
- ...


[Changelog](https://github.com/tuyenvm/OpenKey/blob/master/CHANGELOG.md)

## Cài đặt:
**Cài đặt thủ công:**  
Tải bản OpenKey mới nhất từ [đây](https://github.com/tuyenvm/OpenKey/releases/latest), mở file `dmg` ra rồi kéo thả `OpenKey.app` vào thư mục `Application`.

**Cài bằng Homebrew:** (by nhymxu)  
Nếu chưa cài Homebrew, mở terminal, nhập:
```
$ /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```

Kiểm tra phiên bản OpenKey:
```
$ brew info --cask openkey
```
Gõ lệnh sau để homebrew tự cài OpenKey cho bạn:
```
$ brew install --cask openkey
```

Để update phiên bản mới nhất của OpenKey
```
$ brew upgrade --cask openkey
```

## Note - Lưu ý:
OpenKey cần cấp quyền, vào *System Preferences -> Security & Privacy -> Accessibility*, kích hoạt `OpenKey.app`. **Không tắt nó khi đang dùng OpenKey**.
![Guide](https://raw.githubusercontent.com/tuyenvm/tuyenvm.github.io/master/images/openkey-guide.png "Accessibility").

## OpenKey cho Linux (Fcitx5) — đang thử nghiệm 🧪

> **Trạng thái:** Bản hỗ trợ Linux đang được phát triển dưới dạng **addon cho [Fcitx5](https://fcitx-im.org/)**, dùng lại engine gõ tiếng Việt sẵn có của OpenKey (`Sources/OpenKey/engine`). Tính năng đang trong giai đoạn **thử nghiệm để đảm bảo ổn định trước khi gửi Pull Request** về repo gốc `tuyenvm/OpenKey`. Rất hoan nghênh mọi đóng góp và phản hồi.

Phù hợp nhất với môi trường KDE Plasma / Qt / Wayland (đã thử nghiệm trên Arch Linux + KDE Plasma + Wayland). Engine dùng chung với bản macOS/Windows nên cách gõ tương đương; phần Linux là một lớp "cầu nối" mỏng giữa Fcitx5 và engine, theo mô hình của `fcitx5-unikey`.

### Kiểu gõ & tính năng (bản hiện tại)
- Kiểu gõ: **Telex, VNI, Simple Telex 1/2**.
- Tuỳ chọn: kiểm tra chính tả, đặt dấu kiểu mới (oà/uý), Quick Telex, cho phép Z F W J làm phụ âm, gõ tắt phụ âm đầu/cuối, viết hoa đầu câu, gạch chân preedit.
- Mọi tuỳ chọn được tích hợp sẵn trong **Fcitx5 Configuration** (không cần GUI riêng).
- Bảng mã: hiện hỗ trợ **Unicode** (phù hợp với mọi ứng dụng Linux hiện đại).

### Yêu cầu (Arch Linux)
```bash
sudo pacman -S --needed fcitx5 fcitx5-configtool cmake base-devel
# (tuỳ chọn) để gõ được trong ứng dụng GTK như Firefox:
sudo pacman -S --needed fcitx5-gtk
```
Header và file CMake của Fcitx5 nằm sẵn trong gói `fcitx5` trên Arch (không cần gói `-dev` riêng).

### Cài đặt (Arch — qua PKGBUILD, được pacman quản lý)
```bash
cd Sources/OpenKey/linux/archlinux
makepkg -si
fcitx5 -r        # nạp lại Fcitx5
```
Để build thủ công bằng CMake, xem chi tiết tại [`Sources/OpenKey/linux/README.md`](Sources/OpenKey/linux/README.md).

### Kích hoạt (KDE Plasma / Wayland)
1. *System Settings → Input & Output → Virtual Keyboard* → chọn **Fcitx 5** (trên Wayland, KWin sẽ khởi chạy bộ gõ). Có thể cần **đăng xuất/đăng nhập lại** một lần.
2. Mở **fcitx5-configtool**, thêm **OpenKey** vào danh sách bộ gõ đang dùng (mục tiếng Việt / `vi`).
3. Chuyển bộ gõ bằng phím tắt của Fcitx5 (mặc định **Ctrl+Space**) rồi gõ thử: `tieengs vieejt` → `tiếng việt`.

### Tính năng chưa hỗ trợ (dự kiến bổ sung)
- Gõ tắt (**Macro**).
- Công cụ **chuyển mã** và các bảng mã cũ (TCVN3, VNI-Windows, …) — hiện chỉ Unicode.
- **Smart switch** theo ứng dụng (Fcitx5 đã có sẵn cơ chế nhớ bộ gõ theo ứng dụng).
- GUI bảng điều khiển riêng (hiện dùng giao diện cấu hình của Fcitx5).

### Ghi chú theo distro
- Addon **chạy trên mọi distro có Fcitx5**, cả X11 lẫn Wayland (KWin, GNOME, Sway, Hyprland…). Tuy nhiên **phải build lại từ nguồn trên từng distro** (ABI của Fcitx5 và đường dẫn thư viện khác nhau) — không copy file `.so` sang máy khác.
- **Build deps theo distro:** Arch → `fcitx5 cmake`; Fedora → `cmake gcc-c++ fcitx5-devel` (libdir là `/usr/lib64`, CMake tự xử lý); Debian/Ubuntu → `cmake g++ libfcitx5core-dev libfcitx5config-dev`.
- CMake tự dò đúng đường dẫn cài đặt từ cấu hình của Fcitx5, không cần chỉnh tay.
- Cách bật Fcitx5 khác nhau theo desktop (KDE: Virtual Keyboard; GNOME/khác: autostart + biến môi trường `GTK_IM_MODULE`/`QT_IM_MODULE`/`XMODIFIERS`) — đây là cấu hình của Fcitx5, không liên quan tới addon.

## Tác giả
- Mai Vũ Tuyên.
- Mọi góp ý, gửi cho mình qua maivutuyen.91@gmail.com  
- Fanpage: [https://www.facebook.com/OpenKeyVN](https://www.facebook.com/OpenKeyVN)

## Liên kết
- [OpenKey cho Windows, xem chi tiết tại đây](https://github.com/tuyenvm/OpenKey/tree/master/Sources/OpenKey/win32)
- [OpenKey cho Linux (đang phát triển)](https://github.com/tuyenvm/OpenKey/tree/master/Sources/OpenKey/linux)
## Một điều nhỏ nhoi
Đừng quên ủng hộ tác giả bằng cách mua ly cafe cho tác giả tỉnh ngủ nhé:  
[Buy me a coffee ^^](https://tuyenvm.github.io/donate.html)  
[Redbull cũng được ^^](https://paypal.me/tuyenmai)  
Hoặc trực tiếp qua ví momo:   
![Donate by momo](https://tuyenvm.github.io/images/momo.png "Momo").   

Cảm ơn các bạn rất nhiều.
