module Builders
  class Vagrant < Builder
    TYPE = 'vagrant'

    def inject(builder_def)
      builder_def.merge(
        'output_dir' => (@workspace.artifact_repo / @scroll_name).to_s,
        'skip_add' => false,
      )
    end
  end
end
