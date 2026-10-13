(* Functional statistics calculator: immutable list processing. *)
let mean values =
  let total = List.fold_left ( + ) 0 values in
  float_of_int total /. float_of_int (List.length values)

let median values =
  let sorted = List.sort compare values in
  let n = List.length sorted in
  if n = 0 then invalid_arg "median requires a non-empty list"
  else if n mod 2 = 1 then float_of_int (List.nth sorted (n / 2))
  else
    (float_of_int (List.nth sorted (n / 2 - 1) + List.nth sorted (n / 2))) /. 2.0

let mode values =
  let sorted = List.sort compare values in
  let rec frequencies = function
    | [] -> []
    | x :: xs ->
        let rec count_same count = function
          | y :: ys when y = x -> count_same (count + 1) ys
          | rest -> (count, rest)
        in
        let count, rest = count_same 1 xs in
        (x, count) :: frequencies rest
  in
  let counts = frequencies sorted in
  let highest = List.fold_left (fun best (_, count) -> max best count) 0 counts in
  List.filter_map (fun (value, count) -> if count = highest then Some value else None) counts

let () =
  let values = [4; 2; 7; 2; 9; 4; 2; 6] in
  Printf.printf "Values: 4, 2, 7, 2, 9, 4, 2, 6\n";
  Printf.printf "Mean: %.2f\n" (mean values);
  Printf.printf "Median: %.2f\n" (median values);
  Printf.printf "Mode: ";
  mode values |> List.iteri (fun i value ->
    if i > 0 then Printf.printf ", ";
    Printf.printf "%d" value);
  Printf.printf "\n"
