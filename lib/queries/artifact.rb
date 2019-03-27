module Queries
  class Artifact < Query
    def perform(opts)
      name = opts.scroll_name || (raise '--scroll is required')
      pp @workspace.scroll(name).packer_pure
    end
  end
end
