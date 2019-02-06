let str = ReasonReact.string;

open CurriculumEditor__Types;

type item = (int, string);

type state = {selectedItem: list(item)};

type action =
  | AddItem(item);

let component = ReasonReact.reducerComponent("CurriculumEditor__SelectBox");

let make = (~listOfItems, ~multiSelectCB, _children) => {
  ...component,
  initialState: () => {selectedItem: []},
  reducer: (action, state) =>
    switch (action) {
    | AddItem(item) =>
      ReasonReact.Update({selectedItem: [item, ...state.selectedItem]})
    },
  render: ({state, send}) =>
    <div>
      {
        listOfItems
        |> List.map(((_key, value, status)) =>
             status ?
               <div
                 className="select-list__item-selected flex items-center justify-between bg-grey-lightest text-xs text-grey-dark border rounded p-3 mb-2">
                 {value |> str}
                 <button
                   onClick={
                     _event => {
                       ReactEvent.Mouse.preventDefault(_event);
                       multiSelectCB(_key, value, false);
                     }
                   }>
                   <svg
                     className="w-3"
                     id="fa3b28d3-128c-4841-a4e9-49257a824d7b"
                     xmlns="http://www.w3.org/2000/svg"
                     viewBox="0 0 14 15.99">
                     <path
                       d="M13,1H9A1,1,0,0,0,8,0H6A1,1,0,0,0,5,1H1A1,1,0,0,0,0,2V3H14V2A1,1,0,0,0,13,1ZM11,13a1,1,0,1,1-2,0V7a1,1,0,0,1,2,0ZM8,13a1,1,0,1,1-2,0V7A1,1,0,0,1,8,7ZM5,13a1,1,0,1,1-2,0V7A1,1,0,0,1,5,7Zm8.5-9H.5a.5.5,0,0,0,0,1H1V15a1,1,0,0,0,1,1H12a1,1,0,0,0,1-1V5h.5a.5.5,0,0,0,0-1Z"
                       fill="#525252"
                     />
                   </svg>
                 </button>
               </div> :
               ReasonReact.null
           )
        |> Array.of_list
        |> ReasonReact.array
      }
      <div className="flex relative">
        <div
          className="select-list__group bg-white border rounded rounded-t-none shadow pb-2 w-full">
          <div className="px-3 pt-3 pb-2">
            <input
              className="appearance-none bg-transparent border-b w-full text-grey-darker pb-3 px-2 pl-0 leading-tight focus:outline-none"
              type_="text"
              placeholder="Type to Search"
            />
          </div>
          {
            listOfItems
            |> List.map(((_key, value, status)) =>
                 !status ?
                   <div
                     onClick={
                       _event => {
                         ReactEvent.Mouse.preventDefault(_event);
                         multiSelectCB(_key, value, true);
                       }
                     }
                     className="px-3 py-2 hover:bg-grey-lighter">
                     {value |> str}
                   </div> :
                   ReasonReact.null
               )
            |> Array.of_list
            |> ReasonReact.array
          }
        </div>
      </div>
    </div>,
};