#!/bin/bash

# Путь к исполняемому файлу cub3D
CUB3D_PATH="../cub3D"

# Проверка наличия исполняемого файла cub3D
if [ ! -f "$CUB3D_PATH" ]; then
    echo "Error: cub3D executable not found at $CUB3D_PATH"
    exit 1
fi

# Путь к директории с тестовыми файлами
MAP_DIR="./test_maps"

# Список тестовых файлов
FILES=(
    "test_FC1.cub" "test_FC10.cub" "test_FC11.cub" "test_FC12.cub" "test_FC13.cub"
    "test_FC14.cub" "test_FC2.cub" "test_FC3.cub" "test_FC4.cub" "test_FC5.cub"
    "test_FC6.cub" "test_FC7.cub" "test_FC8.cub" "test_FC9.cub" "test_MAP1.cub"
    "test_MAP10.cub" "test_MAP11.cub" "test_MAP12.cub" "test_MAP13.cub"
    "test_MAP14.cub" "test_MAP15.cub" "test_MAP16.cub" "test_MAP17.cub"
    "test_MAP18.cub" "test_MAP19.cub" "test_MAP2.cub" "test_MAP20.cub"
    "test_MAP21.cub" "test_MAP22.cub" "test_MAP23.cub" "test_MAP24.cub"
    "test_MAP25.cub" "test_MAP26.cub" "test_MAP27.cub" "test_MAP28.cub"
    "test_MAP29.cub" "test_MAP3.cub" "test_MAP30.cub" "test_MAP31.cub"
    "test_MAP32.cub" "test_MAP33.cub" "test_MAP34.cub" "test_MAP35.cub"
    "test_MAP4.cub" "test_MAP5.cub" "test_MAP6.cub" "test_MAP7.cub" "test_MAP8.cub"
    "test_MAP9.cub" "test_W1.cub" "test_W2.cub" "test_W3.cub" "test_W4.cub"
    "test_W5.cub" "test_W6.cub" "test_W7.cub" "test_bonus_map.cub"
    "test_valid_map.cub"
)

# Переменные для учета количества успешных и неудачных тестов
success_count=0
failure_count=0

# Цикл по всем файлам
for file in "${FILES[@]}"; do
    echo "Running test with $file..."
    $CUB3D_PATH "$MAP_DIR/$file" > /dev/null 2>&1

    # Проверка успешности выполнения
    if [ $? -eq 0 ]; then
        echo "$file: Test passed"
        success_count=$((success_count + 1))
    else
        echo "$file: Test failed"
        failure_count=$((failure_count + 1))
    fi
done

# Вывод статистики
echo "-----------------------------------"
echo "Tests passed: $success_count"
echo "Tests failed: $failure_count"
