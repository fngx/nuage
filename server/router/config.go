package router

import (
	. "github.com/mickael-kerjean/nuage/server/common"
	"net/http"
)

func ConfigHandler(ctx App, res http.ResponseWriter, req *http.Request) {
	c, err := ctx.Config.Export()
	if err != nil {
		sendErrorResult(res, err)
		return
	}
	res.Write([]byte("window.CONFIG = "))
	res.Write([]byte(c))
}
