# Program to execute generated inputs automatically
for ($i = 1; $i -lt 11; $i++) {
    $programPath = 'C:\Projects\TP2-Grafos\src\main.exe'
    
    $fileName = "C:\Projects\TP2-Grafos\src\data\Grafo$i.txt"
    $outputLocation = "> C:\Projects\TP2-Grafos\src\results\data\results$i.txt"
    $params = "$fileName $outputLocation"

    Invoke-Expression -Command "$programPath $params" 
}