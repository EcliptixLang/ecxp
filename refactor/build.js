import { glob } from "glob";
import { writeFileSync } from "fs";

const globa = await glob("./**/**/**/*.cpp");
console.log(globa.join(" "))

writeFileSync("hi", `g++ ${globa.join(" ")} -o hi.out`);
