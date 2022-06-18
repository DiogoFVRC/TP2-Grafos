# Program to execute generated inputs automatically
for ($i = 1; $i -lt 11; $i++) {
    $programPath = 'C:/Projects/TP2-Grafos/src/main.exe'
    
    $fileName = "C:/Projects/TP2-Grafos/src/auto/Grafo$i.txt"
    $outputLocation = "> C:/Projects/TP2-Grafos/src/results/auto/results$i.txt"
    $params = "$fileName $outputLocation"

    Invoke-Expression -Command "$programPath $params" 
}