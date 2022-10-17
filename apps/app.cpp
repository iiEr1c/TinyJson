#include <TinyJson.hpp>
#include <string_view>

// https://json-generator.com/
int main() {
  TinyJson::JsonValue val;
  std::string_view input{"\
  {\
    \"code\" : 1, \"msg\" : \"success\", \"data\" : {\
      \"name\" : \"pig\", \"age\" : \"18\", \"sex\" : \"man\", \"hometown\" : {\
        \"province\" : \"江西省\", \"city\" : \"抚州市\", \"county\" : \"崇仁县\"\
      }\
    }\
  }"};
  TinyJson json(input);
  //   for (size_t i = 0; i < 1'000'000; ++i) {
  //     json.parse(&val);
  //   }

  
  std::string_view input2 = R"([
  {
    "_id": "634d1b83b5c98af8215fd5e1",
    "index": 0,
    "guid": "efa2f822-9809-40be-bc32-29d83e13eab5",
    "isActive": true,
    "balance": "$1,912.22",
    "picture": "http://placehold.it/32x32",
    "age": 39,
    "eyeColor": "green",
    "name": "Vincent Hopper",
    "gender": "male",
    "company": "STREZZO",
    "email": "vincenthopper@strezzo.com",
    "phone": "+1 (891) 564-2287",
    "address": "202 Danforth Street, Morgandale, District Of Columbia, 9416",
    "about": "Incididunt minim incididunt non ullamco amet cillum fugiat anim excepteur do minim. In enim dolor aute irure adipisicing eiusmod consequat. Cupidatat occaecat adipisicing do nostrud sit nostrud anim sunt voluptate laboris eiusmod duis commodo ad. Non ad exercitation anim irure ad aute laboris ullamco ipsum in eiusmod. Ullamco eu velit nostrud proident culpa cupidatat consectetur dolore et id velit. Mollit nulla non commodo veniam elit sint esse ex excepteur excepteur. Consectetur deserunt id excepteur fugiat do occaecat ut proident velit dolor.\r\n",
    "registered": "2017-06-11T05:11:37 -08:00",
    "latitude": 56.339714,
    "longitude": 45.894187,
    "tags": [
      "esse",
      "id",
      "et",
      "occaecat",
      "ad",
      "dolore",
      "Lorem"
    ],
    "friends": [
      {
        "id": 0,
        "name": "Rena Powell"
      },
      {
        "id": 1,
        "name": "Margret Stevens"
      },
      {
        "id": 2,
        "name": "Wendy Pickett"
      }
    ],
    "greeting": "Hello, Vincent Hopper! You have 6 unread messages.",
    "favoriteFruit": "strawberry"
  },
  {
    "_id": "634d1b8334ec0efa8e14d10f",
    "index": 1,
    "guid": "bc78b775-7485-452a-b4c1-702bf56e0b38",
    "isActive": true,
    "balance": "$1,438.04",
    "picture": "http://placehold.it/32x32",
    "age": 39,
    "eyeColor": "brown",
    "name": "Kerr Burns",
    "gender": "male",
    "company": "GEEKOLOGY",
    "email": "kerrburns@geekology.com",
    "phone": "+1 (978) 495-3319",
    "address": "120 Lee Avenue, Stonybrook, American Samoa, 9218",
    "about": "Nisi aute eu fugiat aute. Ipsum quis incididunt culpa sit non amet eu dolor consectetur labore cupidatat. Exercitation est aute eiusmod pariatur occaecat nostrud fugiat commodo adipisicing incididunt excepteur dolore non. Consequat fugiat excepteur magna laborum dolore minim magna est labore proident nulla dolor exercitation dolore. Qui est anim quis pariatur aliqua consequat consequat cupidatat elit laborum. Dolor eiusmod amet laboris anim incididunt.\r\n",
    "registered": "2019-11-03T11:36:08 -08:00",
    "latitude": 62.801477,
    "longitude": -83.388582,
    "tags": [
      "ea",
      "nulla",
      "veniam",
      "sunt",
      "do",
      "aute",
      "ex"
    ],
    "friends": [
      {
        "id": 0,
        "name": "Moreno Mcknight"
      },
      {
        "id": 1,
        "name": "Clay Sparks"
      },
      {
        "id": 2,
        "name": "Dillon Moses"
      }
    ],
    "greeting": "Hello, Kerr Burns! You have 1 unread messages.",
    "favoriteFruit": "strawberry"
  },
  {
    "_id": "634d1b8397f47f68bd97b0f3",
    "index": 2,
    "guid": "d464128a-b162-4d26-8bba-a30ef93e056f",
    "isActive": false,
    "balance": "$1,366.99",
    "picture": "http://placehold.it/32x32",
    "age": 27,
    "eyeColor": "green",
    "name": "Bishop Frye",
    "gender": "male",
    "company": "ENTROPIX",
    "email": "bishopfrye@entropix.com",
    "phone": "+1 (872) 445-3318",
    "address": "103 Lois Avenue, Boonville, New Hampshire, 123",
    "about": "Cillum pariatur nostrud nostrud exercitation ipsum id ipsum aliqua in et. Eiusmod nostrud fugiat anim est officia magna aliquip voluptate eiusmod consectetur anim pariatur exercitation. Sit anim et deserunt aute magna.\r\n",
    "registered": "2016-11-13T03:04:35 -08:00",
    "latitude": 70.823946,
    "longitude": 38.496573,
    "tags": [
      "voluptate",
      "cillum",
      "velit",
      "ex",
      "commodo",
      "nisi",
      "laborum"
    ],
    "friends": [
      {
        "id": 0,
        "name": "Colon Torres"
      },
      {
        "id": 1,
        "name": "Luella Griffith"
      },
      {
        "id": 2,
        "name": "Ashley Finley"
      }
    ],
    "greeting": "Hello, Bishop Frye! You have 2 unread messages.",
    "favoriteFruit": "strawberry"
  },
  {
    "_id": "634d1b83698bc3c0024c50ee",
    "index": 3,
    "guid": "290a963f-600b-4b22-b6cd-bebeeea5f279",
    "isActive": false,
    "balance": "$3,642.53",
    "picture": "http://placehold.it/32x32",
    "age": 36,
    "eyeColor": "green",
    "name": "Hatfield Gilliam",
    "gender": "male",
    "company": "COMVEX",
    "email": "hatfieldgilliam@comvex.com",
    "phone": "+1 (993) 520-3473",
    "address": "426 McDonald Avenue, Salix, Georgia, 872",
    "about": "In culpa consequat ad aliqua in exercitation. Minim laboris nulla occaecat adipisicing culpa dolore cupidatat est incididunt excepteur nulla dolor. Consectetur ea reprehenderit duis est ex nulla velit deserunt anim nisi. Commodo culpa excepteur nostrud officia aute ullamco quis ad commodo incididunt. Laborum aute exercitation elit irure sint sint minim enim deserunt deserunt excepteur.\r\n",
    "registered": "2019-11-03T05:04:31 -08:00",
    "latitude": -83.36967,
    "longitude": -90.634735,
    "tags": [
      "est",
      "sint",
      "sit",
      "tempor",
      "do",
      "cillum",
      "nisi"
    ],
    "friends": [
      {
        "id": 0,
        "name": "Bowman Stout"
      },
      {
        "id": 1,
        "name": "Christian Simmons"
      },
      {
        "id": 2,
        "name": "Leah Valencia"
      }
    ],
    "greeting": "Hello, Hatfield Gilliam! You have 7 unread messages.",
    "favoriteFruit": "banana"
  },
  {
    "_id": "634d1b83abaaf93fe2afe6f4",
    "index": 4,
    "guid": "72cdd4c1-9d73-4810-a955-3649593849c7",
    "isActive": true,
    "balance": "$2,480.06",
    "picture": "http://placehold.it/32x32",
    "age": 24,
    "eyeColor": "green",
    "name": "Diana Baldwin",
    "gender": "female",
    "company": "ARTWORLDS",
    "email": "dianabaldwin@artworlds.com",
    "phone": "+1 (846) 599-3968",
    "address": "800 Brighton Court, Johnsonburg, Virgin Islands, 795",
    "about": "Ea sint incididunt et consequat ex occaecat amet sit id labore consequat. Incididunt ea irure anim exercitation ad. Deserunt anim fugiat cillum elit culpa ullamco sit nostrud cupidatat laboris consequat esse. Voluptate qui veniam voluptate ex consectetur. Laboris et aute enim qui enim ea officia excepteur est labore.\r\n",
    "registered": "2016-10-24T06:43:37 -08:00",
    "latitude": -89.104514,
    "longitude": 120.653251,
    "tags": [
      "laboris",
      "do",
      "eiusmod",
      "incididunt",
      "do",
      "dolore",
      "eiusmod"
    ],
    "friends": [
      {
        "id": 0,
        "name": "Wallace Norton"
      },
      {
        "id": 1,
        "name": "Brock Chavez"
      },
      {
        "id": 2,
        "name": "Robin Crane"
      }
    ],
    "greeting": "Hello, Diana Baldwin! You have 6 unread messages.",
    "favoriteFruit": "banana"
  }
])";

  for (size_t i = 0; i < 100'000; ++i) {
    TinyJson json2(input2);
    TinyJson::JsonValue val2;
    json2.parse(&val2);
  }
}
