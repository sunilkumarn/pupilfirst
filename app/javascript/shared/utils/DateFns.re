type locale;

// TODO: This function should return the user's actual / selected timezone.
let currentTimezone = () => "Asia/Kolkata";

// TODO: This function should return either "HH:mm", or "h:mm a" depending on user's preferred time format.
let selectedTimeFormat = () => " HH:mm";

[@bs.module "date-fns-tz"]
external utcToZonedTime: (Js.Date.t, string) => Js.Date.t = "utcToZonedTime";

[@bs.module "date-fns"]
external formatDistanceStrict: (Js.Date.t, Js.Date.t) => string =
  "formatDistanceStrict";

[@bs.deriving abstract]
type formatDistanceStrictOptions = {
  [@bs.optional]
  addSuffix: bool,
  [@bs.optional]
  unit: string,
  [@bs.optional]
  roundingMethod: string,
  [@bs.optional]
  locale,
};

[@bs.module "date-fns"]
external formatDistanceStrictOpt:
  (Js.Date.t, Js.Date.t, formatDistanceStrictOptions) => string =
  "formatDistanceStrict";

let formatDistanceToNowStrictOpt = (date, options) => {
  let zonedTime = utcToZonedTime(date, currentTimezone());
  zonedTime->formatDistanceStrictOpt(Js.Date.make(), options);
};

[@bs.deriving abstract]
type formatOptions = {
  timeZone: string,
  [@bs.optional]
  locale,
  [@bs.optional]
  weekStartsOn: int,
  [@bs.optional]
  firstWeekContainsDate: int,
  [@bs.optional]
  useAdditionalWeekYearTokens: bool,
  [@bs.optional]
  useAdditionalDayOfYearTokens: bool,
};

[@bs.module "date-fns-tz"]
external formatTz: (Js.Date.t, string, formatOptions) => string = "format";

let format = (date, fmt) => {
  let timeZone = currentTimezone();

  // First, get the zoned time.
  let zonedDate = utcToZonedTime(date, timeZone);

  // Then format it, specifying the zone again, so that timezone
  // can be printed correctly.
  formatTz(zonedDate, fmt, formatOptions(~timeZone, ()));
};

let formatPreset = (date, fmt, withTime) => {
  let computedFormat = fmt ++ (withTime ? selectedTimeFormat() : "");
  format(date, computedFormat);
};

/**
 * `formatShorter(date, withTime)` will return a string wih the format 'MMM d'.
 */
let formatShorter = (date, withTime) =>
  formatPreset(date, "MMM d", withTime);

/**
 * `formatShort(date, withTime)` will return a string wih the format 'MMMM d'.
 */
let formatShort = (date, withTime) => formatPreset(date, "MMMM d", withTime);

/**
 * `formatLong(date, withTime)` will return a string wih the format 'MMM d, yyyy'.
 */
let formatLong = (date, withTime) =>
  formatPreset(date, "MMM d, yyyy", withTime);

/**
 * `formatLonger(date, withTime)` will return a string wih the format 'MMMM d, yyyy'.
 */
let formatLonger = (date, withTime) =>
  formatPreset(date, "MMMM d, yyyy", withTime);

[@bs.module "date-fns"]
external parseJSONObject: Js.Json.t => Js.Date.t = "parseJSON";

[@bs.module "date-fns"] external parseJSON: string => Js.Date.t = "parseJSON";

[@bs.module "date-fns"]
external isBefore: (Js.Date.t, Js.Date.t) => bool = "isBefore";

[@bs.module "date-fns"]
external isAfter: (Js.Date.t, Js.Date.t) => bool = "isAfter";

let isPast = date => {
  let zonedTime = utcToZonedTime(date, currentTimezone());
  zonedTime->isAfter(Js.Date.make());
};

let isFuture = date => {
  let zonedTime = utcToZonedTime(date, currentTimezone());
  zonedTime->isBefore(Js.Date.make());
};

[@bs.module "date-fns"]
external differenceInSeconds: (Js.Date.t, Js.Date.t) => int =
  "differenceInSeconds";
