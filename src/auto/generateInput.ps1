# Program to generate inputs using gen.exe
for ($i = 4+12; $i -lt 24; $i++) {
    $genPath = 'C:\Projects\TP2-Grafos\src\gen.exe'
    
    $num = $i - 3
    $fileName = "> Grafo$num.txt"
    #Write-Output $fileName

    $vertexNum = [Math]::Pow(2,$i)-1;
    #Write-Output $vertexNum
    
    $edgeNum = 4*$vertexNum+3;
    #Write-Output $edgeNum
    
    $params = "$vertexNum $edgeNum $fileName"
    #Write-Output $params
    
    #Write-Output "$genPath $params" 
    Invoke-Expression -Command "$genPath $params" 
}