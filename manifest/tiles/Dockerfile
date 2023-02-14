# docker build . -t rootcom/mqtt-tiles
# docker run -it -p 8080:8080 --rm --name water-tiles rootcom/mqtt-tiles
FROM node:16-alpine

WORKDIR /tiles

COPY package*.json ./
RUN yarn global add @quasar/cli

RUN npm install
COPY . .

EXPOSE 8080
CMD [ "quasar", "dev" ]
