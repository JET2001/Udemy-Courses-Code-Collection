const avg_dolphin = (80+70+60)/3, avg_koala = (70+60+50)/3;
function checkGreater100(value)
{
    if (value >= 100) return true;
    else return false;
}
if (avg_dolphin !== avg_koala)
{
    if (checkGreater100(avg_dolphin) && avg_dolphin > avg_koala) console.log("Dolphin");
    else if (checkGreater100(avg_koala)) console.log("Koala");
    else console.log ('Tie'); // both teams lesser than 100 points
}
else console.log("Tie");
