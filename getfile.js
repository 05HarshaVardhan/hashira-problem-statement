const fs = require("fs");

const data = fs.readFileSync("testcase.json", "utf8");
const jsonData = JSON.parse(data);

const points = [];
const outputLines = [];

// Loop through each property in JSON
for (const key in jsonData) {
    if (key === "keys") continue; // skip "keys" object

    const base = parseInt(jsonData[key].base, 10);
    const valueStr = jsonData[key].value;
    const yCoordinate = parseInt(valueStr, base);

    // Push the parsed x and y coordinates to the points array
    points.push({
        x: parseInt(key, 10),
        y: yCoordinate
    });

    // Create a string in "x,y" format for the output file
    outputLines.push(`${parseInt(key, 10)},${yCoordinate}`);
}

// Write the lines to the file, separated by newlines
fs.writeFileSync("coordinates.csv", outputLines.join("\n"));

console.log("Coordinates written to coordinates.csv");