import { sanitizeIdentifier } from '@angular/compiler';
import { Component, HostBinding, OnInit } from '@angular/core';
import {ApiService} from '../api.service';
import { SquareObj } from '../../model/square_obj';

@Component({
  selector: 'app-board',
  templateUrl: './board.component.html',
  styleUrls: ['./board.component.scss']
})
export class BoardComponent implements OnInit{
  squares: SquareObj[];
  xIsNext: boolean;
  winner: string;
  move_type: string;
  cycle: Map<number, string[]>;
  colapse_choice?: string[];
  result: string;
  client_id: number;
  played_once_already: boolean;

  last_idx: number | null;

  @HostBinding("style.--grid-size")
  private grid_size: number = 4;

  constructor(private api:ApiService) {
    this.colapse_choice = [];
    this.cycle = new Map();
    this.client_id = 0;
    this.played_once_already = false;
    this.result = "";
  }

  ngOnInit(): void {
  }

  newGame(size: string) {
    if(size.length === 0){
      return;
    }

    var num = parseInt(size);
    if(num === NaN || num < 2 || num > 5){
      alert("Please enter a size between 2 and 5.");
      return;
    }
    this.grid_size = num;

    this.api.restart(this.client_id, this.grid_size).subscribe(msg => {
      this.xIsNext = true;
      this.winner = "";
      this.last_idx = null;
      this.client_id = msg.board_id;
      this.move_type = "entangle";
      this.result = "pending";
    })
    this.squares = [];
    for (let i = 0; i < this.grid_size * this.grid_size; ++i) {
      this.squares.push(new SquareObj());
    }
    this.played_once_already = true;
  }

  get player() {
    return this.xIsNext ? "X" : "O";
  }

  get gameOver() {
    return this.result !== "pending";
  }

  makeMove(idx: number) {
    if (this.gameOver) {
      console.log("game is over!");
      return;
    }
    if (this.move_type === "entangle") {
      this.makeMoveEntangle(idx);
    }
    else if (this.move_type === "colapse") {
      this.makeMoveColapse(idx);
    }
    else {
      console.log("move", this.move_type, "not implemented");
    }
  }

  makeMoveEntangle(idx: number) {
    if (this.gameOver) {
      console.log("game is over!");
      return;
    }
    if (this.squares[idx].is_colapsed) {
      console.log("this field is already colapsed!");
      return;
    }
    if (this.last_idx === null) {
      this.last_idx = idx;
      return;
    }
    if (this.last_idx === idx) {
      this.last_idx = null;
      return;
    }
    console.log(this.last_idx, idx);

    let last_idx = this.last_idx;

    this.api.entangle(this.client_id, this.last_idx, idx).subscribe(sth => {
      console.log(sth.move_type, sth.player, sth.tic);
      this.update(idx, sth.tic);
      this.update(last_idx, sth.tic);
      if(sth.move_type !== 'colapse'){
        this.xIsNext = sth.player === "x";
      } 
      this.last_idx = null;
      this.move_type = sth.move_type;
      this.cycle = this.objToMap(sth.cycle);
      if (this.move_type === "colapse") {
        let array = Object.entries(sth.cycle);
        console.log(array[0][1], array[1]);
      }
    });
  }


  objToMap(obj: Object) {
    let map = new Map<number, string[]>();
    if (obj === undefined)
      return map;

    let array = Object.entries(obj);

    array.forEach(row => {
      let key = parseInt(row[0]);
      map.set(key, row[1]);
    });
    return map;
  }

  makeMoveColapse(idx: number) {
    if (this.gameOver) {
      console.log("game is over!");
      return;
    }
    this.colapse_choice = this.cycle.get(idx);
    this.last_idx = idx;
  }

  colapse(idx: number) {
    console.log(this.last_idx, this.colapse_choice![idx]);
    this.api.colapse(this.client_id, this.last_idx!, this.colapse_choice![idx]).subscribe(sth => {
      console.log(sth);
      this.colapse_choice = undefined;
      this.cycle.clear();
      let to_colapse = this.objToMap(sth.colapse);
      to_colapse.forEach((val, key) => {
        this.squares[key].tics = val[0];
        this.squares[key].is_colapsed = true;
      });
      this.xIsNext = sth.player === "x";
      this.move_type = sth.move_type;
      this.last_idx = null;
      this.result = sth.result;
      console.log(to_colapse);
    });
  }

  update(idx: number, tic: string) {
    if (!this.squares[idx].tics) {
      this.squares[idx].tics = tic;
    } else {
      let a = this.squares[idx].tics;
      this.squares[idx].tics = a.concat(", ", tic);
    }
  }

}
