#ifndef WEB_PAGE_H
#define WEB_PAGE_H

#include <Arduino.h>
#include "wifi_manager.h"
#include "modes.h"

String renderWebPage() {

    String html;

    html += F(
"<!DOCTYPE html>\n"
"<html lang=\"fr\">\n"
"<head>\n"
"<meta charset=\"UTF-8\">\n"
"<title>" PROJECT_NAME "</title>\n"

"<style>\n"
"body{margin:0;font-family:system-ui,sans-serif;background:#0f172a;color:#e5e7eb;padding:20px;text-align:center;}\n"
"h1{margin:10px 0 5px;font-size:2rem;font-weight:800;color:#facc15;text-shadow:0 0 10px #facc15;}\n"
".version{opacity:0.7;margin-bottom:20px;font-size:0.9rem;}\n"
".ip{background:#1e293b;padding:8px 16px;border-radius:20px;display:inline-block;margin-bottom:20px;font-size:0.9rem;opacity:0.8;}\n"

".grid{display:grid;grid-template-columns:repeat(auto-fit,minmax(130px,1fr));gap:14px;margin-bottom:20px;}\n"
".btn{padding:16px 10px;border-radius:18px;font-weight:700;text-decoration:none;color:#111;font-size:1rem;box-shadow:0 4px 12px rgba(0,0,0,0.4);transition:0.1s;display:flex;align-items:center;justify-content:center;cursor:pointer;}\n"
".btn.active{outline:4px solid white;box-shadow:0 0 15px white;transform:scale(1.05);}\n"

".zen{background:#6ee7b7;}.amb{background:#86efac;}.vague{background:#67e8f9;}.arc{background:#f472b6;}\n"
".arcturbo{background:#fb7185;}.pulsev{background:#4ade80;}.pulsej{background:#facc15;}.pulser{background:#f87171;}\n"
".rush{background:#ef4444;color:white;}.k2000{background:#a855f7;color:white;}.disco{background:#fb7185;}\n"
".jackpot{background:#facc15;}.fdj{background:#4ade80;}.gagnant{background:#22c55e;}.perdant{background:#f87171;}\n"
".util{background:#e5e7eb;color:#111;}\n"

"#submode-container{min-height:60px;margin-bottom:25px;display:flex;justify-content:center;align-items:center;gap:10px;}\n"
".sub-btn{padding:6px 12px;border-radius:10px;background:#334155;color:#e5e7eb;font-size:0.85rem;font-weight:600;cursor:pointer;box-shadow:0 2px 6px rgba(0,0,0,0.4);}\n"
".sub-btn.active{background:#3b82f6;color:white;box-shadow:0 0 10px #3b82f6;}\n"

".color-dot{width:42px;height:42px;border-radius:50%;display:inline-block;border:3px solid #ffffff33;box-shadow:0 0 6px rgba(0,0,0,0.4);cursor:pointer;}\n"
".color-active{border:3px solid white;box-shadow:0 0 12px white;}\n"

".card{background:#1e293b;padding:16px;border-radius:14px;margin-top:20px;text-align:left;max-width:520px;margin:auto;}\n"
"input[type=\"number\"]{width:60px;padding:6px;border-radius:8px;border:none;margin-right:10px;background:#334155;color:white;}\n"
"input[type=\"submit\"]{margin-top:10px;padding:8px 14px;border-radius:10px;border:none;background:#3b82f6;color:white;font-weight:700;cursor:pointer;}\n"

"</style>\n"

"<script>\n"

"function setMode(m){ fetch('/mode/' + m); }\n"
"function setSub(v){ fetch('/sub?v=' + v); }\n"
"function setHumeur(c){ fetch('/mode/humeur?c=' + c); }\n"

"function refresh(){\n"
" fetch('/status')\n"
" .then(r=>r.json())\n"
" .then(s=>{\n"

"   document.querySelectorAll('.btn').forEach(b=>{\n"
"       b.classList.toggle('active', parseInt(b.dataset.mode) === s.mode);\n"
"   });\n"

"   const container = document.getElementById('submode-container');\n"
"   container.innerHTML = '';\n"

"   let modes = {\n"
"       5:['🐢 Lent','🚶 Normal','🏃 Rapide'],\n"
"       6:['🐢 Lent','🚶 Normal','🏃 Rapide'],\n"
"       7:['🐢 Lent','🚶 Normal','🏃 Rapide'],\n"
"       3:['➡️ Normal','⬅️ Inversé'],\n"
"       4:['Normal','Turbo'],\n"
"       8:['➡️ Avant','⬅️ Arrière'],\n"
"       9:['🐢 Lent','🚶 Normal','🏃 Rapide'],\n"
"       10:['🐢 Lent','🚶 Normal','🏃 Rapide']\n"
"   };\n"

"   if(modes[s.mode]){\n"
"       modes[s.mode].forEach((txt,i)=>{\n"
"           let b=document.createElement('div');\n"
"           b.className='sub-btn'+(i===s.sub?' active':'');\n"
"           b.textContent=txt;\n"
"           b.onclick=()=>setSub(i);\n"
"           container.appendChild(b);\n"
"       });\n"
"   }\n"

"   document.querySelectorAll('.color-dot').forEach((c,i)=>{\n"
"       c.classList.toggle('color-active', i===s.humeur);\n"
"   });\n"

" });\n"
"}\n"

"setInterval(refresh, 300);\n"

"</script>\n"

"</head>\n"
"<body>\n"

"<h1>" PROJECT_NAME "</h1>\n"
"<div class=\"version\">Version " PROJECT_VERSION "</div>\n"

"<div class=\"ip\">IP : ");

    html += getCurrentIP();
    html += F("</div>\n");
    // ---------------------------------------------------------
    // MODES DOUX (alignés sur TON enum)
    // ---------------------------------------------------------

    html += F("<h2>🌿 Modes doux</h2><div class=\"grid\">");

    html += "<div class=\"btn zen\" data-mode=\"0\" onclick=\"setMode('zen')\">Zen</div>";
    html += "<div class=\"btn amb\" data-mode=\"1\" onclick=\"setMode('ambiance')\">Ambiance</div>";
    html += "<div class=\"btn vague\" data-mode=\"2\" onclick=\"setMode('vague')\">Vague</div>";
    html += "<div class=\"btn arc\" data-mode=\"3\" onclick=\"setMode('arc')\">Arc-en-ciel</div>";
    html += "<div class=\"btn arcturbo\" data-mode=\"4\" onclick=\"setMode('arc_turbo')\">Arc-en-ciel Turbo</div>";
    html += "<div class=\"btn pulsev\" data-mode=\"5\" onclick=\"setMode('pulse_vert')\">Pulse Vert</div>";
    html += "<div class=\"btn pulsej\" data-mode=\"6\" onclick=\"setMode('pulse_jaune')\">Pulse Jaune</div>";
    html += "<div class=\"btn pulser\" data-mode=\"7\" onclick=\"setMode('pulse_rouge')\">Pulse Rouge</div>";

    html += "</div>";

    // ---------------------------------------------------------
    // ZONE FIXE POUR LES SOUS-MODES
    // ---------------------------------------------------------

    html += "<div id=\"submode-container\"></div>";

    // ---------------------------------------------------------
    // MODES DYNAMIQUES
    // ---------------------------------------------------------

    html += F("<h2>🔥 Modes dynamiques</h2><div class=\"grid\">");

    html += "<div class=\"btn rush\" data-mode=\"8\" onclick=\"setMode('rush')\">Rush</div>";
    html += "<div class=\"btn k2000\" data-mode=\"9\" onclick=\"setMode('k2000')\">K2000</div>";
    html += "<div class=\"btn disco\" data-mode=\"10\" onclick=\"setMode('disco')\">Disco</div>";
    html += "<div class=\"btn jackpot\" data-mode=\"11\" onclick=\"setMode('jackpot')\">Jackpot</div>";
    html += "<div class=\"btn fdj\" data-mode=\"12\" onclick=\"setMode('fdj')\">FDJ Winner</div>";
    html += "<div class=\"btn gagnant\" data-mode=\"13\" onclick=\"setMode('client_gagnant')\">Gagnant</div>";
    html += "<div class=\"btn perdant\" data-mode=\"14\" onclick=\"setMode('client_perdant')\">Perdant</div>";

    html += "</div>";

    // ---------------------------------------------------------
    // UTILITAIRES
    // ---------------------------------------------------------

    html += F("<h2>🧱 Utilitaires</h2><div class=\"grid\">");

    html += "<div class=\"btn util\" data-mode=\"15\" onclick=\"setMode('ouverture')\">Ouverture</div>";
    html += "<div class=\"btn util\" data-mode=\"16\" onclick=\"setMode('fermeture')\">Fermeture</div>";
    html += "<div class=\"btn util\" data-mode=\"17\" onclick=\"setMode('pause')\">Pause café</div>";
    html += "<div class=\"btn util\" data-mode=\"18\" onclick=\"setMode('maintenance')\">Maintenance</div>";
    html += "<div class=\"btn util\" data-mode=\"19\" onclick=\"setMode('humeur')\">Humeur du Patron</div>";

    html += "</div>";
    // ---------------------------------------------------------
    // HUMEUR DU PATRON — toujours visible (mode 19)
    // ---------------------------------------------------------

    html += F("<h2>😎 Humeur du Patron</h2><div style=\"display:flex;justify-content:center;gap:10px;\">");

    const char* colors[6] = {
        "#22c55e",  // vert
        "#facc15",  // jaune
        "#ef4444",  // rouge
        "#3b82f6",  // bleu
        "#a855f7",  // violet
        "#ffffff"   // blanc
    };

    for (int i = 0; i < 6; i++) {
        html += "<span class=\"color-dot\" style=\"background:";
        html += colors[i];
        html += "\" onclick=\"setHumeur(" + String(i) + ")\"></span>";
    }

    html += "</div>";

    // ---------------------------------------------------------
    // MODE AUTOMATIQUE
    // ---------------------------------------------------------

    html += F(
"<h2>🕒 Mode automatique</h2>\n"
"<div class=\"card\">\n"
"<form action=\"/auto\" method=\"GET\">\n"
"<label>Heure ouverture : <input type=\"number\" name=\"morning\" min=\"0\" max=\"23\" value=\"");

    html += String(autoMorningHour);

    html += F("\"></label><br>\n"
"<label>Heure fermeture : <input type=\"number\" name=\"evening\" min=\"0\" max=\"23\" value=\"");

    html += String(autoEveningHour);

    html += F("\"></label><br>\n"
"<label><input type=\"checkbox\" name=\"enabled\" value=\"1\"");

    if (autoModeEnabled) html += " checked";

    html += F(
"> Activer le mode automatique</label><br>\n"
"<input type=\"submit\" value=\"Enregistrer\">\n"
"</form>\n"
"</div>\n"
"</body>\n"
"</html>\n");

    return html;
}

#endif
