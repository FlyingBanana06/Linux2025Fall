BASE_DIR="."
COMPRESS_DIR="$BASE_DIR/compressed_files"
ID_FILE="$BASE_DIR/student_id"

# Step 1. 建立資料夾
echo "[1/5] 建立分類資料夾..."
mkdir -p "$COMPRESS_DIR/zip" "$COMPRESS_DIR/tar.gz" "$COMPRESS_DIR/rar" "$COMPRESS_DIR/unknown"

# Step 2. 分類壓縮檔
echo "[2/5] 分類壓縮檔中..."
for file in "$COMPRESS_DIR"/*; do
    [[ -f "$file" ]] || continue  # 若不是檔案則跳過
    case "$file" in
        *.zip)     mv "$file" "$COMPRESS_DIR/zip/" ;;
        *.tar.gz)  mv "$file" "$COMPRESS_DIR/tar.gz/" ;;
        *.rar)     mv "$file" "$COMPRESS_DIR/rar/" ;;
        *)         mv "$file" "$COMPRESS_DIR/unknown/" ;;
    esac
done

# Step 3. 生成 missing_list / wrong_list
echo "[3/5] 檢查缺交與錯誤格式..."
missing_list="$BASE_DIR/missing_list"
wrong_list="$BASE_DIR/wrong_list"
> "$missing_list"
> "$wrong_list"

while read -r id; do
    # 檢查該學號是否有壓縮檔
    found_file=$(find "$COMPRESS_DIR" -type f -name "${id}.*" | head -n 1)
    if [ -z "$found_file" ]; then
        echo "$id" >> "$missing_list"
    else
        # 若副檔名不符合格式，記入 wrong_list
        case "$found_file" in
            *.zip|*.tar.gz|*.rar) ;; # 正確格式
            *) echo "$id" >> "$wrong_list" ;;
        esac
    fi
done < "$ID_FILE"

# === Step 4. 解壓縮所有合法檔案 ===
echo "[4/5] 解壓縮中..."
for dir in zip rar tar.gz; do
    for file in "$COMPRESS_DIR/$dir"/*; do
        [[ -f "$file" ]] || continue
        folder_name=$(basename "$file" | cut -d. -f1)
        target_dir="$COMPRESS_DIR/$dir/$folder_name"
        mkdir -p "$target_dir"

        case "$dir" in
            zip)
                unzip -q "$file" -d "$target_dir"
                ;;
            rar)
                unrar x -idq "$file" "$target_dir"
                ;;
            tar.gz)
                tar -xzf "$file" -C "$target_dir"
                ;;
        esac
    done
done

# Step 5. 結果報告
echo "[5/5] 全部完成 ✅"
echo "------------------------------------"
echo "缺交名單已輸出至: $missing_list"
echo "格式錯誤名單已輸出至: $wrong_list"
echo "分類結果在: $COMPRESS_DIR/{zip,tar.gz,rar,unknown}/"
echo "------------------------------------"

