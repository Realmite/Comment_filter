@echo off
setlocal enabledelayedexpansion

:: Очистка итогового файла
echo. > output\all_results.txt

:: Обработка всех 9 тестов
for /L %%i in (1,1,9) do (
    set TEST_ID=%%i
    set INPUT_FILE=testInput\test_!TEST_ID!.cpp
    set EXPECTED_FILE=expectedOutput\expected!TEST_ID!.cpp
    set OUTPUT_FILE=output\actual_output!TEST_ID!.cpp
    set TEMP_RESULT_FILE=output\results!TEST_ID!.txt

    :: Заголовок теста
    echo ============================== >> output\all_results.txt
    echo TEST CASE !TEST_ID! >> output\all_results.txt
    echo ============================== >> output\all_results.txt

    :: Ожидаемый результат
    echo Expected output: >> "!TEMP_RESULT_FILE!"
    type "!EXPECTED_FILE!" >> "!TEMP_RESULT_FILE!"
    echo( >> "!TEMP_RESULT_FILE!"

    :: Запуск тестируемой программы
    CommentFilter.exe "!INPUT_FILE!" "!OUTPUT_FILE!" > nul

    :: Полученный результат
    echo Received output: >> "!TEMP_RESULT_FILE!"
    type "!OUTPUT_FILE!" >> "!TEMP_RESULT_FILE!"
    echo( >> "!TEMP_RESULT_FILE!"
    echo( >> "!TEMP_RESULT_FILE!"

    :: Запись в общий файл
    type "!TEMP_RESULT_FILE!" >> output\all_results.txt
)

endlocal
pause
